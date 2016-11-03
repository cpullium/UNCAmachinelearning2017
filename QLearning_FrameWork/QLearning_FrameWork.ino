/* QLearning_FrameWork
  - This is a framework for the implimentation of Q_Learning on an arduino.
  
  Note: 
  
  The action variable is ecoded as:
  
  0  1  2
  
  3     4
        
  5  6  7

*/


//Pre-Processing
//***************************************************************************
#include "Arduino.h"                        //attaches all linked files
#include <Servo.h>                          //servo library
#include <Encoder.h>                        //for wheel encoders 
#include <Wire.h>                           // I2C libraries (LCD uses that)
#include <Adafruit_RGBLCDShield.h>          
#include <utility/Adafruit_MCP23017.h>
#include "functions.h"
#include "macros.h"



//Q Learning Parameters--------------------------------------------------------
float alpha = 0.8;          //Learning Rate 
float K=0;                 //Exploration Reward
float gamma = .3;         //Value of look ahead

bool epsilon_greedy = 1;      //of 1 take random action sometimes
int epsilon = 0.6;           //percentage of random actions
//-------------------------------------------------------------------------------

//State Space Variables--------------------------------------------------------
float Q[5][5][8];          //Quaility of taking action given a state
float N[5][5][8];         //Number of times visiting a state
float N_Init = 0.01;     //Can't initialize to zero, it's used in division 

int S1 = 2;             //State of "Elbow" Servo
int S2 = 2;            //State of "Shoulder" Servo

int S1_Prime;           //temporary next states -> "Elbow"
int S2_Prime;          //temporary next states -> "Shoulder"

int next_S1=0;          //actual state moved into -> "Elbow"
int next_S2=0;         //actual state moved into -> "Shoulder"

int Valid_Actions[8];               //Available actions avaiable given current states
int Actions_Num;                    //Number of available actions 
int Valid_Actions_Prime[8];         //Avaialble in a neighboring state
int Actions_Num_Prime;              //Number available in neighbor states

int Visited[5][5] = {0};
int Action_Next = 0;       //Action to be taken
float R;                 //Reward recieved from wheel encoders 
//------------------------------------------------------------------------------

//Switch Case
int mode = 0;
int init_state = 0;
int pause_state = 0;

//LCD
uint8_t buttons = 0;   //Which button is pushed on the LCD panel

//Debugging variables----------
unsigned int States_Visited = 0;    //Tracking how much it's explored
float time_elapsed;                 //Time used in debugging 
bool flag = 0;


//Objects----------------------------------------------------------
Servo Shoulder;  // create servo object to control a servo 
Servo Elbow;  // twelve servo objects can be created on most boards
Encoder myEnc(3, 4);//create encoder object 
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield(); //LCD Screen
//-------------------------------------------------------------------


//SETUP
void setup(){ 
  
  Serial.begin(9600);
 
  
 
  Shoulder.attach(24);  // attaches the servo on pin 11 to the servo object
  Elbow.attach(22);      
  lcd.begin(16, 2);
  lcd.setBacklight(VIOLET);
  lcd.setCursor(0,2);
  lcd.print("Thinking cap on");

  
  //Initialize LEDs
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);  
  delay(3000);
  lcd.clear();


} 


//MAIN LOOP
//*******************************************************************************
void loop() {

  unsigned int iterations =0;
  float Start_Pos;
  
  switch(mode){
    case LOAD_INIT:
      switch(init_state){
        case 0:
            print_Begin();
            buttons = lcd.readButtons();
            if(buttons){ 
              if (buttons & BUTTON_SELECT) {
                 lcd.print("BEGIN LEARNING");
                 lcd.setBacklight(TEAL);
                 delay(50);
                 Init_All(0);
                 mode = LEARN_BEHAVIOR;
                 break;
              }
              else if (buttons & BUTTON_DOWN) {   
                 init_state++;
              }
              else flash_Error(); 
            }
             
        break;
        case 1:
            print_Load(1);
            buttons = lcd.readButtons();
            if(buttons){ 
              if (buttons & BUTTON_SELECT) {
                 lcd.print("BEGIN LEARNING");
                 lcd.setBacklight(TEAL);
                 delay(500);
                 mode = LEARN_BEHAVIOR;
                 break;
              }
              else if (buttons & BUTTON_DOWN) {   
                 init_state++;
              }
              else if (buttons & BUTTON_UP) {   
                 init_state--;
              }
              else flash_Error(); 
            }            
        break;
        
        case 2:
            print_Load(2);
            buttons = lcd.readButtons();
            if(buttons){ 
              if (buttons & BUTTON_SELECT) {
                 lcd.print("LEARNING");
                 lcd.setBacklight(TEAL);
                 delay(500);
                 mode = LEARN_BEHAVIOR;
                 break;
              }
              else if (buttons & BUTTON_DOWN) {   
                 init_state++;
              }
              else if (buttons & BUTTON_UP) {   
                 init_state--;
              }
              else flash_Error(); 
            }
        break;
        
        case 3:
            print_Load(3);
            buttons = lcd.readButtons();
            if(buttons){ 
              if (buttons & BUTTON_SELECT) {
                 lcd.print("LEARNING");
                 lcd.setBacklight(TEAL);
                 delay(500);
                 mode = LEARN_BEHAVIOR;
                 break;
              }
              else if (buttons & BUTTON_UP) {   
                 init_state--;
              }
              else flash_Error(); 
            }            
        break;    
        
        default:
            flash_Error();
        break;
      }  
    break; //end learning switch

    case LEARN_BEHAVIOR: // Engage in learning process until "select" button is pushed
      while(!(buttons & BUTTON_SELECT)){
          lcd.clear();
    
          Debug_Visited_States(0);  // if (0), no serial print out. 
          
          Policy(); //Policy
          
          //Measure where you start from
          Start_Pos = myEnc.read();
          
          //Move to new state assign next_S1, next_S2. Increment global N[S1][S2][A];
          take_Action();
          
          //Measure where you end
          R = myEnc.read()-Start_Pos;
          //R *= -1;
          Serial.println(R);
         
          //Update Q synchronously. 
          Q_Update();//All inputs are global variables
    
          //Setup for next itteration
          N[S1][S2][Action_Next]++;
          alpha -= 0.0001;
          if(alpha < .01) alpha = .01;
          S1 = next_S1;
          S2 = next_S2;
          iterations++;//Count iterations
          
          buttons = lcd.readButtons(); // Check for buttons being pushed 
      }
      mode = PAUSE_SAVE;  
    break;  
    
    case PAUSE_SAVE:
      lcd.clear();
      lcd.setBacklight(BLUE);
      lcd.setCursor(3,0);
      lcd.print("PAUSED");
      delay(1000);
      while(!(buttons)){buttons = lcd.readButtons();};
      if (buttons & BUTTON_SELECT) {
         lcd.print("LEARNING");
         lcd.setBacklight(TEAL);
         delay(500);
         mode = LEARN_BEHAVIOR;
      }
      else flash_Error();
      
    break;
    
    default:
    break;
  
  
  }//end switch
}//end loop




