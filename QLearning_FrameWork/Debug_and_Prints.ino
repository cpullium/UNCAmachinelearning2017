#include "Arduino.h"
#include "functions.h"
#include "macros.h"

//Q Learning Parameters--------------------------------------------------------
extern float alpha;          //Learning Rate 
extern float K;                 //Exploration Reward
extern float gamma;         //Value of look ahead

extern bool epsilon_greedy;      //of 1 take random action sometimes
extern int epsilon;           //percentage of random actions
//-------------------------------------------------------------------------------

//State Space Variables--------------------------------------------------------
extern float Q[5][5][8];          //Quaility of taking action given a state
extern float N[5][5][8];         //Number of times visiting a state
extern float N_Init;     //Can't initialize to zero, it's used in division 

extern int S1;             //State of "Elbow" Servo
extern int S2;            //State of "Shoulder" Servo

extern int S1_Prime;           //temporary next states -> "Elbow"
extern int S2_Prime;          //temporary next states -> "Shoulder"

extern int next_S1;          //actual state moved into -> "Elbow"
extern int next_S2;         //actual state moved into -> "Shoulder"

extern int Valid_Actions[8];               //Available actions avaiable given current states
extern int Actions_Num;                    //Number of available actions 
extern int Valid_Actions_Prime[8];         //Avaialble in a neighboring state
extern int Actions_Num_Prime;              //Number available in neighbor states

extern int Action_Next;       //Action to be taken
extern float R;                 //Reward recieved from wheel encoders 
//------------------------------------------------------------------------------

//Switch Case
extern int mode;
extern int init_state;
extern int pause_state;

//LCD
extern uint8_t buttons;   //Which button is pushed on the LCD panel

//Debugging variables----------
extern unsigned int States_Visited;    //Tracking how much it's explored
extern float time_elapsed;                 //Time used in debugging 
extern bool flag;

//DEBUG SECTION*******************************************************************************************************************
//dedbug run through all positions
void Debug_Servo_State_Run(void){
  
  for(int i=0; i<5; i++){
   for(int j=0; j<5; j++){
      Shoulder.write(70+20*i);
      Elbow.write(40+20*j);
      delay(500);
   } 
  }
  
}

void Debug_Visited_States(bool print_on){
    //Print Debug the number of states visited------------------------------------------------------------------------
   for(int i=0; i < 5; i++){
      for(int j=0; j < 5; j++){
        
        if(Visited[i][j] != 0) States_Visited++;
        
      }
    }
    
    if(print_on){
      Serial.print(States_Visited); Serial.print("......."); Serial.print(S1); Serial.print(", "); Serial.print(S2);
      Serial.print("  Time: "); time_elapsed = millis(); time_elapsed = time_elapsed/60000; Serial.print(time_elapsed);
      Serial.print(" minutes"); Serial.print("    "); Serial.print(myEnc.read()); Serial.print(" NetProgress");
      Serial.print("    ");  Serial.print("alpha: "); Serial.print(alpha); Serial.print("   Reward: ");
    }
    
    if(States_Visited == 25) digitalWrite(GREEN2, HIGH);
    
    States_Visited = 0;
    Visited[S1][S2]++;
 //---------------------------------------------------------------------------------------------------------------------
}

//**********************************************************************************************************************************

//PRINT SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void print_Begin(void){
  lcd.clear();
  lcd.print("SELECT TO BEGIN");
  lcd.setCursor(0, 1);
  lcd.print("DOWN TO LOAD");
}

void flash_Error(void){
  for(int i=0;i<3;i++){
    lcd.setBacklight(RED);
    delay(250);
    lcd.setBacklight(WHITE);
    delay(250);
  }
}

void print_Load(int num){
  lcd.clear();
  lcd.setBacklight(YELLOW);
  lcd.print("Load");
  lcd.setCursor(7,0);
  lcd.print(num);
  delay(50);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
