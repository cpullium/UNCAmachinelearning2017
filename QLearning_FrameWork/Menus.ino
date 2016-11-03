#include "functions.h"
#include "macros.h"


//Switch Cases
extern int mode;
extern int init_state;
extern int save_state;

//LCD
extern uint8_t buttons;   //Which button is pushed on the LCD panel

//Memory 
extern int block_ptr1;
extern int block_ptr2;


void init_Menu(void){
  switch(init_state){
          case 0:
              print_Begin();
              while(!(buttons)) buttons = lcd.readButtons();
                if(buttons){ 
                  if (buttons & BUTTON_SELECT) {
                     delay(250);
                     print_Q();
                     mode = LEARN_BEHAVIOR;
                  }
                  else if (buttons & BUTTON_DOWN) {   
                     delay(250);
                     init_state++;
                  }
                  else flash_Error(); 
                }  
                buttons = 0;
          break;
          case 1:
              print_Load(1);
              while(!(buttons)) buttons = lcd.readButtons();
              if(buttons){ 
                if (buttons & BUTTON_SELECT) {
                     lcd.clear();
                     lcd.setCursor(4,0);
                     lcd.print("LOADING");
                     lcd.setBacklight(RED);
                     Load_Map(block_ptr1, 5, 5, 8);
                     print_Q();
                     delay(1000);
                     lcd.clear();
                     lcd.setCursor(4,0);
                     lcd.print("LOADED");
                     lcd.setBacklight(TEAL);
                     delay(2000);
                     init_state = 0;
                }
                else if (buttons & BUTTON_DOWN) { 
                   delay(250);  
                   init_state++;
                }
                else if (buttons & BUTTON_UP) {   
                   delay(250);
                   init_state--;
                }
                else flash_Error(); 
              }           
              buttons = 0; 
          break;
          
          case 2:
              print_Load(2);
              while(!(buttons)) buttons = lcd.readButtons();
              if(buttons){ 
                if (buttons & BUTTON_SELECT) {
                     lcd.clear();
                     lcd.setCursor(4,0);
                     lcd.print("LOADING");
                     lcd.setBacklight(RED);
                     Load_Map(block_ptr2, 5, 5, 8);
                     delay(1000);
                     lcd.clear();
                     lcd.setCursor(4,0);
                     lcd.print("LOADED");
                     lcd.setBacklight(TEAL);
                     delay(2000);
                     init_state = 0;
                }
                else if (buttons & BUTTON_UP) {   
                   delay(250);
                   init_state--;
                }
                else flash_Error(); 
              }
              buttons = 0;
          break;
            
          default:
              flash_Error();
          break;
        }//end switch
}   

void save_Menu(void){
      switch(save_state){
              case 0:
                  print_Pause();
                  while(!(buttons)) buttons = lcd.readButtons();
                    if(buttons){ 
                      if (buttons & BUTTON_SELECT) {
                         delay(250);
                         mode = LEARN_BEHAVIOR;
                      }
                      else if (buttons & BUTTON_DOWN) {   
                         delay(250);
                         save_state++;
                      }
                      else flash_Error(); 
                    }  
                    buttons = 0;
              break;
              case 1:
                  print_Save(1);
                  while(!(buttons)) buttons = lcd.readButtons();
                  if(buttons){ 
                    if (buttons & BUTTON_SELECT) {
                   lcd.clear();
                   lcd.setCursor(4,0);
                   lcd.print("SAVING");
                   lcd.setBacklight(RED);
                   print_Q();
                   Save_Map(block_ptr1, 5, 5, 8);
                   delay(1000);
                   lcd.clear();
                   lcd.setCursor(4,0);
                   lcd.print("SAVED");
                   lcd.setBacklight(BLUE);
                   delay(2000);
                   save_state = 0;
                    }
                    else if (buttons & BUTTON_DOWN) { 
                       delay(250);  
                       save_state++;
                    }
                    else if (buttons & BUTTON_UP) {   
                       delay(250);
                       save_state--;
                    }
                    else flash_Error(); 
                  }           
                  buttons = 0; 
              break;
              
              case 2:
                  print_Save(2);
                  while(!(buttons)) buttons = lcd.readButtons();
                  if(buttons){ 
                    if (buttons & BUTTON_SELECT) {
                       lcd.clear();
                       lcd.setCursor(4,0);
                       lcd.print("SAVING");
                       lcd.setBacklight(RED);
                       Save_Map(block_ptr2, 5, 5, 8);
                       delay(1000);
                       lcd.clear();
                       lcd.setCursor(4,0);
                       lcd.print("SAVED");
                       lcd.setBacklight(BLUE);
                       delay(2000);
                       save_state = 0;
                    }
                    else if (buttons & BUTTON_UP) {   
                       delay(250);
                       save_state--;
                    }
                    else flash_Error(); 
                  }
                  buttons = 0;
              break;
              
              
              default:
                  flash_Error();
              break;
            }    
}

