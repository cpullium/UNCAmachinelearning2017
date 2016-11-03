#include <EEPROM.h> 

//function prototypes
void Save_Map(int block, int S1_Size, int S2_Size, int Act_Size);
void Store_Q(float Q_Val, int block, int Offset);
void Load_Map(int block, int S1_Size, int S2_Size, int Act_Size);
void Load_Q(int S1_index, int S2_index, int A_index, int block, int Offset);


//global variables
extern int block_ptr1 = 0;
extern int block_ptr2 = 801;
extern int block_ptr3 = 1602;

extern float Q[5][5][8]

void Save_Map(int block, int S1_Size, int S2_Size, int Act_Size){
  int i=0, j=0, k=0;                              // indices for Q map
  int Offset;
  for(i=0; i < S1_Size; i++){                   
    for(j=0; j < S2_Size; j++){
      for(k=0; k < Act_Size; k++){                  // for all Q[i][j][k]
        Offset = (i*Act_Size*S2_Size + (j*Act_Size) + k) << 2;    // set the offset from the block pointer to the address for current q-value
        Store_Q(Q[i][j][k], block, Offset);             // store current q-value
      }
    }
  }
}

void Store_Q(float Q_Val, int block, int Offset){
  int addr_ptr = block + Offset;                 		 // address pointer for Q-value being stored
    EEPROM.put(addr_ptr, Q_Val);               		 // write float to EEPROM
}

void Load_Map(int block, int S1_Size, int S2_Size, int Act_Size){
  int i, j, k;                              // indices for Q map
  int Offset;
  for(i=0; i < S1_Size; i++){                   
    for(j=0; j < S2_Size; j++){
      for(k=0; k < Act_Size; k++){                  // for all Q[i][j][k]
        Offset = (i*Act_Size*S2_Size + (j*Act_Size) + k) << 2;    // set the EEPROM offset for the current Q-value 
        Load_Q(i, j, k, block, Offset);
      }
    }
  }
}

void Load_Q(int S1_index, int S2_index, int A_index, int block, int Offset){
  int addr_ptr = block + Offset;                   // set EEPROM address pointer for current Q-value
  EEPROM.get(addr_ptr, Q[S1_index][S2_index][A_index]);
}

