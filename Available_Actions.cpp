#include "Arduino.h"
int Valid_Actions[8];
int Actions_Num;
int Vaild_Actions_Prime[8];
int Actions_Num_Prime;

int S1 = 2;//Set initial state (2,2)
int S2 = 2;
int S1_Prime;
int S2_Prime;

int Available_Actions(State1, State2, Action_Type){

	int z[3] = {-1,0,1};
	int Action_Being_Checked;
	int Array_Adress;
	
	if (Action_Type == 0) Actions_Num = 0;
	else Actions_Num_Prime = 0; 

	for(int i=0; i<3; i++){
		for (int j=0; j<3; j++){

			S1_Prime = S1 + z[i];
			S2_Prime = S2 + z[j];

			if(S1_Prime != S1 && S2_Prime != S2){ //If not staying in the same space

				if(S1_Prime >= 0 && S1_Prime <= 4){ //Within S1 Boundrys
					if(S2_Prime >= 0 && S2_Prime <= 4){

							if (Action_Type == 0) Vaild_Actions[Actions_Num] = a;
							else Valid_Actions_Prime[Actions_Num_Prime] = a;
							Array_Adress++
							
					}
				}
				Action_Being_Checked++; //As long as it's not the same space, increment 
			}	
		}
	}
}