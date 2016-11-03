#include "Arduino.h"
#include "functions.h"
#include "macros.h"
#include <Servo.h> 

extern Servo Shoulder; 
extern Servo Elbow;  // twelve servo objects can be created on most boards
extern int S1;                //State where updates are taking place
extern int S2;                //State where updates are taking place

extern float Q[5][5][8]; 				//Quality of taking an action state pair
extern float N[5][5][8];			// Number of times you've taken an action state pair
extern float N_Init;

extern int Valid_Actions[8];
extern int Valid_Actions_Prime[8];


/********************************************************** 
void Init_All(void);
	Calls all initiation functions.


*/
void Init_All(bool Loading){
  digitalWrite(GREEN1, HIGH);
  Init_QandN(Loading);
	Init_Valid_Actions();
  Shoulder.write(130);
  Elbow.write(130);
	
}

/********************************************************** 
void Init_QandN(void);
	Initializes the Q and N arrays. Q gets 0s and N gets 
	all 1s.


*/
void Init_QandN(bool loading){
	int i;
	int j;
	int k;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			for(k=0;k<8;k++){
      
      if(!(loading)) Q[i][j][k] = 0 ;
			N[i][j][k] = N_Init;
      
			}
		}
	}
}

/********************************************************** 
void Init_Valid_Actions(void);
	Initializes the Valid_Actions and Valid Actions prime
        vector to 0. 


*/
void Init_Valid_Actions(void){
	int i;
	for(i=0;i<8;i++){
		Valid_Actions[i]=0;
    Valid_Actions_Prime[i]=0;
	}
}
