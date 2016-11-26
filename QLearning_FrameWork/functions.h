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
void Servo_Test(void);

//intializations
void Init_All(bool);
void Init_QandN(bool);
void Init_Valid_Actions(void);

void Debug_Visited_States(bool);
void Debug_Servo_State_Run(void);

void print_Begin(void);
void print_Pause(void);
void flash_Error(void);
void print_Load(int num);
void print_Save(int num);
void print_Q(void);

//functions for menus
void init_Menu(void);
void save_Menu(void);
//function prototypes for Q-storage
void Save_Map(int block, int S1_Size, int S2_Size, int Act_Size);
void Load_Map(int block, int S1_Size, int S2_Size, int Act_Size);


void Create_Reward_Map(void);
void printRewardMap(void);
void Step_Through(void);
void init_Typed_QandN(void);

#endif
