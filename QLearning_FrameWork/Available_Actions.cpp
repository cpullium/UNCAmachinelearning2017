#include "Arduino.h"
#include "functions.h"

extern int Valid_Actions[8]; 		
extern int Actions_Num;				//index of the maximum valid action
extern int Valid_Actions_Prime[8];
extern int Actions_Num_Prime;		//index of the maximum valid action in next state

extern int S1_Prime;         //Temp for possible states
extern int S2_Prime;        //Temp for possible states

//-----------------------------------------------------------------------------------------------------
/* Function Description:
	This function looks at each possible next states and it's action pair. If the state is within
	the boundry conditions of the state space, it puts it's action pair into a global array.
	It also updates a global integer that hold the number of actions put into that array.  

   Written by: 
	Corey Pullium -----------------------------------------------------------------------------------*/

void Available_Actions(int State1,int State2,bool Action_Type){
	int temp1, temp2;
	int z[3] = {-1,0,1};
	int Action_Being_Checked;

	temp1 = S1_Prime; //store current value
	temp2 = S2_Prime; //store current value
	
	if (Action_Type == 0) Actions_Num = 0;      //case of rewriting action vector, reset index/max
	else Actions_Num_Prime = 0;                //case of rewriting action_prime vector, reset index/max

	for(int i=0; i<3; i++){				   //step through S1 possibilities 
		for (int j=0; j<3; j++){		  //step through S2 possibilities

			S1_Prime = State1 + z[i];		//caculate next possible state address for s1
			S2_Prime = State2 + z[j];		//caculate next possible state address for S2

			if(S1_Prime != State1 && S2_Prime != State2){     //Avoid one case, where both states stay the same

				if(S1_Prime >= 0 && S1_Prime <= 4){      //Is it within S1 Boundaries?
					if(S2_Prime >= 0 && S2_Prime <= 4){ //Is it within S2 Boundaries?

							if (Action_Type == 0){     					//if looking for actions in current state
								Valid_Actions[Actions_Num] = Action_Being_Checked; //put approved action in array 
								Actions_Num++; 								  //index/max of the array increments 
							}
							else { 											   //if looking for actions in surrounding states
								Valid_Actions_Prime[Actions_Num_Prime] = Action_Being_Checked; //put approved action in array
								Actions_Num_Prime++; 								      //index/max of the array increments 
							}
					}
				} 
				Action_Being_Checked++; //As long as it's not the same space, increment 
			} 
		}
	} 	
	S1_Prime = temp1; //restore values
	S2_Prime = temp2; //restore values
} //end Function
