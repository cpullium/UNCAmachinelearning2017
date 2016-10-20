/*---------------------------------------------------------------------------------------------------------------------------
      This function contains functions related to the Policy
      int Policy(void)
      int Q_max_action(void)
      void S_Given_A(int State1, int State2, int a)
----------------------------------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "functions.h"

extern bool epsilon_greedy;
extern int epsilon;
extern int S1;
extern int S2;
extern int S1_Prime;
extern int S2_Prime;
extern int Action_Next;
extern int Valid_Actions[8];
extern int Actions_Num;
extern int Valid_Actions_Prime[8];
extern int Actions_Num_Prime;    //index of the maximum valid action in next state
extern float Q[5][5][8];


int Policy(void){
  /* Title: Policy 
   * Author: Jordan Miller
   * this function checks to see if the policy is greedy or epsilon-greedy
   * it returns the action to take according to the specified policy
   */
  int Action_Next;
  int temp; // used to temporarily store action index
  int p = random(100);

 

  if(epsilon_greedy && p < epsilon){    //if epsilon greedy and random action is selected
      temp = random(Actions_Num);       //pick a random action
      Action_Next = Valid_Actions[temp];
  }

  else{
      Action_Next = Q_max_action(S1, S2, 0);          //act greedy
  }

  return Action_Next;
}

int Q_max_action(int State1, int State2, bool Action_Type){
/*Title: Q_max_action
 * returns the action index associated with the best Q value for current state
 * eventually, there would be a way to randomly choose between actions with equal qualities
*/
	int i;
	int temp;
	int Q_max=0;
	int Best_Action;

	if(Action_Type == 0){
		for(i=0; i < Actions_Num; i++){
  			temp = Valid_Actions[i]; //store action associated with index i
  			Q_max = Q[State1][State2][i] > Q_max ? Q[State1][State2][i] : Q_max;
		}
	}
	else if(Action_Type == 1){
		for(i=0; i < Actions_Num_Prime; i++){
  			temp = Valid_Actions_Prime[i]; //store action associated with index i
  			Q_max = Q[State1][State2][i] > Q_max ? Q[State1][State2][i] : Q_max;
		}
	}
   	Best_Action = temp;
  	return Best_Action;
}

void S_Given_A(int State1, int State2, int Action){ 
  /* 
   * Author: Jordan Miller
   * Description: updates globals S1_Prime & S2_Prime
   * given a particular action
   */
  switch(Action){
    case 0:
      S1_Prime = State1-1;
      S2_Prime = State2-1;
      break; 
    case 1:
      S1_Prime = State1-1;
      S2_Prime = State2;
      break; 
    case 2:
      S1_Prime = State1-1;
      S2_Prime = State2+1;
      break; 
    case 3:
      S1_Prime = State1;
      S2_Prime = State2-1;
      break;     
    case 4:
      S1_Prime = State1;
      S2_Prime = State2+1;
      break;     
    case 5:
      S1_Prime = State1+1;
      S2_Prime = State2-1;
      break;     
    case 6:
      S1_Prime = State1+1;
      S2_Prime = State2;
      break;     
    case 7:
      S1_Prime = State1+1;
      S2_Prime = State2+1;
      break;     
  }
}
