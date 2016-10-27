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
#include "Arduino.h"
#include <Servo.h> 
#include <Encoder.h>
#include <LiquidCrystal.h>
#include "functions.h"
#include "macros.h"



//Q Learning Parameters
float alpha =0.5; //Learning Rate 
float gamma = 1; //Incentive Variable
float K=3; //Exploration Reward
bool epsilon_greedy = 0;
int epsilon = 0;
float Q[5][5][8];
float N[5][5][8];

int Valid_Actions[8];
int Actions_Num;
int Valid_Actions_Prime[8];
int Actions_Num_Prime;




int S1 = 2;//Set initial state (2,2)
int S2 = 2;
int S1_Prime;
int S2_Prime;
int next_S1=0;
int next_S2=0;
int Action_Next = 0;  //Action
float R;


//Objects
Servo Shoulder;  // create servo object to control a servo 
Servo Elbow;  // twelve servo objects can be created on most boards
Encoder myEnc(2, 3);//create encoder object 
LiquidCrystal lcd(42, 44, 46, 48, 50, 52);



//SETUP
void setup(){ 
  
  Serial.begin(9600);
 
  Init_All(); //Q gets 0s, N gets 1s.
 
  Shoulder.attach(24);  // attaches the servo on pin 11 to the servo object
  Elbow.attach(22);      
  lcd.begin(16, 2);
  lcd.print(" Teach me how to dougie");
  lcd.setCursor(0,1);
  lcd.print(" to dougie");
  
  //Initialize LEDs
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);  
  delay(3000);


} 





//MAIN LOOP
//*******************************************************************************
void loop() {
// Local Variables
unsigned int iterations =0;
float Start_Pos;

  while(1){
      //Use S1,S2 and Q Table to define next states
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(Actions_Num); 
      lcd.setCursor(0,1);
      lcd.print(S1);
      lcd.setCursor(6,1);
      lcd.print(S2);

      Serial.print("Current Qaulity:   "); Serial.print(S1); Serial.print(", "); Serial.print(S2); Serial.print(" :    ");
      for(int i=0; i < 8; i++){
        Serial.print(Q[S1][S2][i]); Serial.print(", "); 
      }
      Serial.println();
      
      Policy(); //Policy
      
      //Measure where you start from
      //Start_Pos = myEnc.read();
      
      //Move to new state assign next_S1, next_S2. Increment global N[S1][S2][A];
      take_Action();
      
      //Measure where you end
      //R = myEnc.read()-Start_Pos;
      
      
      //Update Q synchronously. 
      Q_Update();//All inputs are global variables
      Serial.print("updated Qaulity:   "); Serial.print(S1); Serial.print(", "); Serial.print(S2); Serial.print(" :    ");
      for(int i=0; i < 8; i++){
        Serial.print(Q[S1][S2][i]); Serial.print(", "); 
      }
      Serial.println();
      Serial.println();
      //Setup for next itteration
      N[S1][S2][Action_Next]++;
      S1 = next_S1;
      S2 = next_S2;
      iterations++;//Count iterations
      delay(250);
  }  
}




