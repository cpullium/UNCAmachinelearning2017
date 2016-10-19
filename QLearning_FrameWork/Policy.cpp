/*---------------------------------------------------------------------------------------------------------------------------
      This function contains functions related to the Policy
      int Policy(void)
      int Q_max_action(void)
      void S_Given_A(int State1, int State2, int a)
----------------------------------------------------------------------------------------------------------------------------*/


#include "Arduino.h"

extern int S1;
extern int S2;
extern int S1_Prime;
extern int S2_Prime;
extern int Valid_Actions[8];
extern int Actions_Num;


int Policy(){
  /* Title: Policy 
   * Author: Jordan Miller
   * this function checks to see if the policy is greedy or epsilon-greedy
   * it returns the action to take according to the specified policy
   */
  int Action;
  int temp; // used to temporarily store action index
  int p = random(100);

  Available_Actions(S1, S2, 0);

  if(epsilon_greedy && p < epsilon){    //if epsilon greedy and random action is selected
      temp = random(Actions_Num);       //pick a random action
      Action = Valid_Actions[temp];
  }

  else{
      Action = Q_max_action();          //act greedy
  }

  return Action;
}

int Q_max_action(){
/*Title: Q_max_action
 * returns the action index associated with the best Q value for current state
 * eventually, there would be a way to randomly choose between actions with equal qualities
 */
  int i;
  int temp;
  int Q_max=0;
  int Best_Action;

  for(i=0; i <= Actions_Num; i++){
      temp = Valid_Actions[i]; //store action associated with index i
      Q_max = if(Q[S1][S2][i] > qmax) ? Q[S1][S2][i] : qmax;
  }
   
  return Best_Action;
}

void S_Given_A(int State1, int State2, int Action){
  /* 
   * Author: Jordan Miller
   * Description: updates globals S1_prime & S2_prime
   * given a particular action
   */
  switch(Action){
    case 0:
      State1_prime = S1-1;
      State2_prime = S2-1;
      break; 
    case 1:
      State1_prime = S1-1;
      State2_prime = S2;
      break; 
    case 2:
      State1_prime = S1-1;
      State2_prime = S2+1;
      break; 
    case 3:
      State1_prime = S1;
      State2_prime = S2-1;
      break;     
    case 4:
      State1_prime = S1;
      State2_prime = S2+1;
      break;     
    case 5:
      State1_prime = S1+1;
      State2_prime = S2-1;
      break;     
    case 6:
      State1_prime = S1+1;
      State2_prime = S2;
      break;     
    case 7:
      State1_prime = S1+1;
      State2_prime = S2+1;
      break;     
  }
}