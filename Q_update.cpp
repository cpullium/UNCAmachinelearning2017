#include "Arduino.h"

extern float Q[5][5][8];
extern unsigned int N[5][5][8];
extern int Valid_Actions[8]; 		
extern int Actions_Num;				//index of the maximum valid action
extern int Vaild_Actions_Prime[8];
extern int Actions_Num_Prime;		//index of the maximum valid action in next state
extern float alpha; 
extern int K;

extern int S1_Prime;         //Temp for possible states
extern int S2_Prime;        //Temp for possible states


void Q_Update(){
  int a = 0;
  int Reward = 0;
  int beta; 
  beta = (1-alpha);

  for(int i; i<Actions_Num; i++){
  	a = Valid_Actions[i];

  	S_Given_A(a);
  	Available_Actions(S1_Prime,S2_Prime,ACT_PRIME);
  	for (int j=0; j<Actions_Num_Prime; j++){
  		S_Given_A(Valid_Actions[j]);
  		A_Prime = Qmax(S1_Prime,S2_Prime);
  		qmax = Q[S1_Prime][S2_Prime][A_Prime];
  	}
  	Reward = if(a == action_taken) ? R : 0;
  	oldPerspective = Q[S1][S2][a];
  	newPerspective = Reward + qmax + K/N[S1_Prime][S2_Prime][A_Prime];
  	Q[S1][S2][a] = beta*oldPerspective + alpha*newPerspective;
  }
}
