/* QLearning_FrameWork
  - This is a framework for the implimentation of Q_Learning on an arduino.
  
  Note: 
  
  The action variable is ecoded as:
  
  0  1  2
  
  3     4
        
  7  6  5

*/


//INITIALIZATION
//***************************************************************************
#include <Servo.h> 
#include <Encoder.h>

//#define SERVO_NUM 2
//#define ACTION_NUM (POW(3,SERVO_NUM)-1)
//#define SEV1_TOTALSTATES 5
//#define SEV2_TOTALSTATES 5
#define ACT 0
#define ACT_PRIME 1

//Q Learning Parameters
float alpha =.95; //Learning Rate 

float gamma =.8; //Incentive Variable

int K=100; //Exploration Reward




float Q[5][5][8];
unsigned int N[5][5][8];

int Available_Actions[8];
int Available_Actions_Prime[8];


int S1 = 2;//Set initial state (2,2)
int S2 = 2;
int S1_Prime;
int S2_Prime;
int next_S1=0;
int next_S2=0;
int A;  //Action
int R;
 
//Objects
Servo S1_servo;  // create servo object to control a servo 
Servo S2_servo;  // twelve servo objects can be created on most boards
Encoder myEnc(2, 3);//create encoder object 




//SETUP
/*******************************************************************************
void setup()
  -Run once before main loop
*/
void setup(){ 
  
  Serial.begin(9600);
 
  init_Arrays(); //Q gets 0s, N gets 1s.
 
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
    next_Move(S1,S2); //Policy
    
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
    itterations++;//Count itterations
}  
}




//FUNCTIONS TO WRITE
/*********************************************************************************


void init_Arrays()
//********************************************************************************
  -Arguments - None
  -Returns - Nothing
  
  Description: Initializes Q array to 0. Initializes N array to 1.

  Written By: Travers Thurman
*/
void init_Arrays(){
  int i = 0;
  int j = 0;
  int k = 0;
  
  //Populate Q with zeros
  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      for(k=0;k<4;k++){  
        Q[i][j][k]=0;
        N[i][j][k]=1;
      }
    }
  }  
}



//void next_Move();
/*********************************************************************************
  -Arguments - None but globals S1,S2 are used 
  -Returns - Changes A;
  
  Description: Chooses a direction based on max q values from where you are. If
    there are multiple values to choose from, pick a random one. Never return an
    illegal action. (something that reaches a boundary)

  Written by:
*/
void next_Move(int S1,int S2){

}



//void take_Action(A);
/*********************************************************************************
  -Arguments - A is an integer representing action
  -Returns - Nothing but changes S1_next, and S2_next. Also increments N[S1][S2][A];
  
  Description: Decodes the action variable and turns it into angle inputs for the 
     servos. Writes new angles to the servos. Changes the global variables S1_next, and 
     S2_next based on the current state and the action given. Increments N[S1][S2][A].
     
     
  Written by:Travers
*/
void take_Action(){
  
  next_S1 = 0;
  next_S2 = 0;
  N[S1][S2][A]++;  
}



//void Q_Update(float R);
/*********************************************************************************
  -Arguments - R is the reward. Uses globals S1,S2,S1_Prime,S2_Prime, N array and Q array 
  -Returns - Nothing but changes Q array.
  
  Description: Impliments the Q algorithm synchronously; meaning it updates all actions 
  in previous state after a move. Since we are looking at all possible actions, here wi use little (a).
     
     
  Written by: Corey Pullium
*/

void Q_Update(){
  Act_Num = Available_Actions(S1, S2, ACT);
  for int i
    Q[S1][S2][a] = (1-alpha)*Q[S1][S2][a] + alpha(Reward() + Qmax + (k/N[............. 
}

//jordan was here
