//=================================
// include guard
#ifndef __FUNCTIONS_H_INCLUDED__
#define __FUNCTIONS_H_INCLUDED__




void Policy(void); 
void take_Action(void); 
void Q_Update(void); 
int Q_max_action(int State1, int State2, bool ); //used by policy and qupdate
void Available_Actions(int State1, int State2, bool Action_Type); //changes global array and returns counter 
void S_Given_A(int State1,int State2,int Action); // changes global S1_Prime, S2_Prime 

//intializations
void Init_All(void);
void Init_QandN(void);
void Init_Valid_Actions(void);

#endif
