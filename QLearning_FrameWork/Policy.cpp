/*---------------------------------------------------------------------------------------------------------------------------
      This function contains functions related to the Policy
      int Policy(void)
      int Q_max_action(void)
      void S_Given_A(int State1, int State2, int a)
----------------------------------------------------------------------------------------------------------------------------*/
#include "Arduino.h"
#include "functions.h"
#include "macros.h"

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


void Policy(void){
  /* Title: Policy 
   * Author: Jordan Miller
   * this function checks to see if the policy is greedy or epsilon-greedy
   * it returns the action to take according to the specified policy
   */
  int temp; // used to temporarily store action index
  int p = random(100);
 
  Available_Actions(S1,S2,0);
  
  if(epsilon_greedy && p < epsilon){    //if epsilon greedy and random action is selected
      temp = random(Actions_Num - 1);       //pick a random action
      Action_Next = Valid_Actions[temp];
  }

  else{
      
      Action_Next = Q_max_action(S1, S2, 0);          //act greedy
  }

  
  Action_Next = Q_max_action(S1, S2, 0);
}

int Q_max_action(int State1, int State2, bool Action_Type){
/*Title: Q_max_action
 * returns the action index associated with the best Q value for current state
 * eventually, there would be a way to randomly choose between actions with equal qualities
*/
	int i;
  int j=0;
  int select;
	int a;  //action being checked
	int Q_max=0;
	int Best_Action;
  int Best_Actions[8]; //stores actions of equal best quality
  int Best_Actions_Size=0; // stores dynamic size of Best Actions array
  
	if(Action_Type == 0){
    Best_Action = Valid_Actions[0];
		for(i=0; i < Actions_Num; i++){
  			a = Valid_Actions[i]; //store action associated with index i
  			if (Q[State1][State2][a] > Q_max){
  			  Q_max = Q[State1][State2][a];
  			   Best_Action = a;
			  }
		}
	}
	else if(Action_Type == 1){
		for(i=0; i < Actions_Num_Prime; i++){
  			a = Valid_Actions_Prime[i]; //store action associated with index i
  			
  			if (Q[State1][State2][a] > Q_max){
  			 Q_max = Q[State1][State2][a];
  			 Best_Action = a;
			}
		}
	}
 
 for(i=0; i < Actions_Num; i++){
      a = Valid_Actions[i];
      if(Q[State1][State2][a] == Q_max){
        Best_Actions[j] = a;
        j++;
      }
   }
   Best_Actions_Size = j;
  
   if(Best_Actions_Size > 1){
    select = random(0 , Best_Actions_Size);
    Best_Action = Best_Actions[select];
   }
    
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
