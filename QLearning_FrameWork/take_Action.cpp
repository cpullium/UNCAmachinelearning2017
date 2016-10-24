#include "Arduino.h"
#include "functions.h"
#include "Servo.h"
#include "macros.h"

extern int S1;
extern int S2;
extern int S1_Prime;
extern int S2_Prime;
extern int next_S1;
extern int next_S2; 
extern int Action_Next;
extern Servo Shoulder; 
extern Servo Elbow;  // twelve servo objects can be created on most boards


void take_Action(void){
  digitalWrite(RED1, HIGH);
	S_Given_A(S1,S2,Action_Next);
	
	next_S1 = S1_Prime;
	next_S2 = S2_Prime;
	
	Shoulder.write(90+20*next_S1);
	Elbow.write(90+20*next_S2);
  delay(1000);
  digitalWrite(RED1, LOW);
}
