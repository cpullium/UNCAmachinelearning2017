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
#include "functions.h"

#define ACT 0
#define ACT_PRIME 1



//Q Learning Parameters
float alpha =.95; //Learning Rate 
float gamma =.8; //Incentive Variable
float K=100; //Exploration Reward
bool epsilon_greedy = 0;
int epsilon = 0;
float Q[5][5][8];
unsigned int N[5][5][8];

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
int Action_Next;  //Action
float R;
 
//Objects
Servo S1_servo;  // create servo object to control a servo 
Servo S2_servo;  // twelve servo objects can be created on most boards
Encoder myEnc(2, 3);//create encoder object 


//SETUP
void setup(){ 
  
  Serial.begin(9600);
 
  Init_All(); //Q gets 0s, N gets 1s.
 
  S1_servo.attach(11);  // attaches the servo on pin 11 to the servo object
  S2_servo.attach(12);       
} 





//MAIN LOOP
//*******************************************************************************
void loop() {
// Local Variables
unsigned int itterations =0;
float Start_Pos;

  while(1){
      //Use S1,S2 and Q Table to define next states
   Action_Next =  Policy(); //Policy
      
      //Measure where you start from
      Start_Pos = myEnc.read();
      
      //Move to new state assign next_S1, next_S2. Increment global N[S1][S2][A];
      take_Action();
      
      //Measure where you end
      R = myEnc.read()-Start_Pos;
      
      //Update Q synchronously. 
   Q_Update();//All inputs are global variables
      
      //Setup for next itteration
      S1 = next_S1;
      S2 = next_S2;
      itterations++;//Count iterations
  }  
}




