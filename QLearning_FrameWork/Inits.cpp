#include "Arduino.h"
#include "functions.h"

extern float Q[5][5][8]; 				//Quality of taking an action state pair
extern unsigned int N[5][5][8];			// Number of times you've taken an action state pair

extern int Valid_Actions[8];
extern int Vaild_Actions_Prime[8];

/********************************************************** 
void Init_All(void);
	Calls all initiation functions.


*/
void Init_All (void){
	Init_QandN();
	Init_Valid_Actions();
	
}

/********************************************************** 
void Init_QandN(void);
	Initializes the Q and N arrays. Q gets 0s and N gets 
	all 1s.


*/
void Init_QandN(void){
	int i;
	int j;
	int k;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			for(k=0;k<8;k++){
				Q[i][j][k] = 0;
				N[i][j][k] = 1;
			}
		}
	}
}

/********************************************************** 
void Init_Valid_Actions(void);
	Initializes the Valid_Actions and Valid Actions prime
        vector to 0. 


*/
void Init_Valid_Actions(void){
	int i;
	for(i=0;i<8;i++){
		Valid_Actions[i]=0;
                Vaild_Actions_Prime[i]=0;
	}
}
