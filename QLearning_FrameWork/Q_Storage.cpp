#include "Arduino.h"    
#include <EEPROM.h> 
#include "functions.h"
#include "macros.h"
                    


////global variables
//extern int block_ptr1;
//extern int block_ptr2;
//extern int block_ptr3;

extern float Q[5][5][8];         //Quality of taking an action state pair
extern float N[5][5][8];      // Number of times you've taken an action state pair

void Save_Map(int block, int S1_Size, int S2_Size, int Act_Size){
  int i=0, j=0, k=0;                              // indices for Q map
  int Offset;
  for(i=0; i < S1_Size; i++){                   
    for(j=0; j < S2_Size; j++){
      for(k=0; k < Act_Size; k++){                  // for all Q[i][j][k]
        int addr_ptr = block + Offset;                      // address pointer for Q-value being stored
        EEPROM.put(addr_ptr, Q[i][j][k]);                   // write float to EEPROM
      }
    }
  }

  block += MEM_BLK_SIZE;                                             // move block pointer to a second block for the N-matrix
    for(i=0; i < S1_Size; i++){                   
    for(j=0; j < S2_Size; j++){
      for(k=0; k < Act_Size; k++){                                 // for all Q[i][j][k]
        Offset = (i*Act_Size*S2_Size + (j*Act_Size) + k) << 2;    // set the offset from the block pointer to the address for current q-value
        int addr_ptr = block + Offset;                            // address pointer for Q-value being stored
        EEPROM.put(addr_ptr, N[i][j][k]);                         // write float to EEPROM
      }
    }
  }
}


void Load_Map(int block, int S1_Size, int S2_Size, int Act_Size){
  int i, j, k;                              // indices for Q map
  int Offset;
  for(i=0; i < S1_Size; i++){                   
    for(j=0; j < S2_Size; j++){
      for(k=0; k < Act_Size; k++){                                  // for all Q[i][j][k]
        Offset = (i*Act_Size*S2_Size + (j*Act_Size) + k) << 2;     // set the EEPROM offset for the current Q-value 
          int addr_ptr = block + Offset;                           // set EEPROM address pointer for current Q-value
          EEPROM.get(addr_ptr, Q[i][j][k]);
      }
    }
  }
  block += MEM_BLK_SIZE;                                           // move block pointer to a second block for the N-matrix
  for(i=0; i < S1_Size; i++){                   
    for(j=0; j < S2_Size; j++){
      for(k=0; k < Act_Size; k++){                                // for all N[i][j][k]
        Offset = (i*Act_Size*S2_Size + (j*Act_Size) + k) << 2;    // set the EEPROM offset for the current Q-value 
          int addr_ptr = block + Offset;                          // set EEPROM address pointer for current Q-value
          EEPROM.get(addr_ptr, N[i][j][k]);
      }
    }
  }
}



