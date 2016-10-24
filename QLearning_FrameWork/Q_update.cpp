#include "Arduino.h"
#include "functions.h"
#include "macros.h"

extern float Q[5][5][8]; 				//Quality of taking an action state pair
extern unsigned int N[5][5][8];			// Number of times you've taken an action state pair

extern int Valid_Actions[8]; 		
extern int Valid_Actions_Prime[8]; 
extern int Actions_Num;				//index of the maximum valid action

extern int Action_Next;       //Action taken, possibly recieving +/- reward.
extern int S1;                //State where updates are taking place
extern int S2;                //State where updates are taking place
extern int S1_Prime;         //Temp for possible states
extern int S2_Prime;        //Temp for possible states

extern float R;     //Reward for action actually taken
extern float alpha; //learning rate
extern float K;				//Exploration factor
//-----------------------------------------------------------------------------------------------------
/* Function Description:
	After transitioning into a new state. The function looks back at the previous state, 
	and updates the map of action qualities. This is a SYNCHRONOUS update; meaning, it updates 
	all actions in that state, even if it wasn't the action taken. 
	
	Factors include: learning rate (alpha), reward(Reward), a one step look ahead(qmax),
	and an exploration factor(K).

   Written by: 
	Corey Pullium -------------------------------------------------------------------------------------*/

void Q_Update(){
  int Action_Being_Updated = 0;        //start at zero
  int A_Prime;             //action in next state set
  int Reward = 0; 				//zero unless updating actual action taken
  float qmax;
  float beta; 					//just a place for 1-alpha
  beta = (1-alpha);

  float oldPerspective;
  float newPerspective;

  for(int i=0; i<Actions_Num; i++){		//Update all possible actions' quaility 
  	Action_Being_Updated = Valid_Actions[i];  //pull from  global valid action vector

  	S_Given_A(S1, S2, Action_Being_Updated);     //translate watched action into a state set
  	Available_Actions(S1_Prime,S2_Prime, 1); //Then update an array of actions in that state

    A_Prime = Q_max_action(S1_Prime, S2_Prime, 1); 		//search array for the best quality action
  	qmax = Q[S1_Prime][S2_Prime][A_Prime]; //store the value of that action

  	Reward = (Action_Being_Updated == Action_Next) ? R : 0; //if looking at the actual action taken, factor in Reward

  	oldPerspective = Q[S1][S2][Action_Being_Updated];  //store current map value
  	newPerspective = Reward + qmax + K/(float)N[S1_Prime][S2_Prime][A_Prime]; //store information learned

  	Q[S1][S2][Action_Being_Updated] = beta*oldPerspective + alpha*newPerspective; //Combined current map with learned info
  																				//beta and alpha weight old vs new
  }
}

