#include "Arduino.h"
#include "functions.h"
#include "macros.h"

//Q Learning Parameters--------------------------------------------------------
extern float alpha;          //Learning Rate 
extern float K;                 //Exploration Reward
extern float gamma;         //Value of look ahead

extern bool epsilon_greedy;      //of 1 take random action sometimes
extern int epsilon;           //percentage of random actions
//-------------------------------------------------------------------------------

//State Space Variables--------------------------------------------------------
extern float Q[5][5][8];          //Quaility of taking action given a state
extern float N[5][5][8];         //Number of times visiting a state
extern float R_map[5][5][8];

extern float N_Init;     //Can't initialize to zero, it's used in division 

extern int S1;             //State of "Elbow" Servo
extern int S2;            //State of "Shoulder" Servo

extern int S1_Prime;           //temporary next states -> "Elbow"
extern int S2_Prime;          //temporary next states -> "Shoulder"

extern int next_S1;          //actual state moved into -> "Elbow"
extern int next_S2;         //actual state moved into -> "Shoulder"

extern int Valid_Actions[8];               //Available actions avaiable given current states
extern int Actions_Num;                    //Number of available actions 
extern int Valid_Actions_Prime[8];         //Avaialble in a neighboring state
extern int Actions_Num_Prime;              //Number available in neighbor states

extern int Action_Next;       //Action to be taken
extern float R;                 //Reward recieved from wheel encoders 
//------------------------------------------------------------------------------

//Switch Case
extern int mode;
extern int init_state;
extern int pause_state;

//LCD
extern uint8_t buttons;   //Which button is pushed on the LCD panel

//Debugging variables----------
extern unsigned int States_Visited;    //Tracking how much it's explored
extern float time_elapsed;                 //Time used in debugging 
extern bool flag;

//DEBUG SECTION*******************************************************************************************************************
//dedbug run through all positions
void Debug_Servo_State_Run(void){
  
  for(int i=0; i<5; i++){
   for(int j=0; j<5; j++){
      Shoulder.write(20*i);
      Elbow.write(20*j);
      delay(500);
   } 
  }
  
}

void Debug_Visited_States(bool print_on){
    //Print Debug the number of states visited------------------------------------------------------------------------
   for(int i=0; i < 5; i++){
      for(int j=0; j < 5; j++){
        
        if(Visited[i][j] != 0) States_Visited++;
        
      }
    }
    
    if(print_on){
      Serial.print(States_Visited); Serial.print("......."); Serial.print(S1); Serial.print(", "); Serial.print(S2);
      Serial.print("  Time: "); time_elapsed = millis(); time_elapsed = time_elapsed/60000; Serial.print(time_elapsed);
      Serial.print(" minutes"); Serial.print("    "); Serial.print(myEnc.read()); Serial.print(" NetProgress");
      Serial.print("    ");  Serial.print("alpha: "); Serial.print(alpha); Serial.print("   Reward: ");
    }
    
    if(States_Visited == 25) digitalWrite(GREEN2, HIGH);
    
    States_Visited = 0;
    Visited[S1][S2]++;
 //---------------------------------------------------------------------------------------------------------------------
}

//**********************************************************************************************************************************

//PRINT SECTION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void print_Begin(void){
  lcd.clear();
  lcd.print("SELECT TO BEGIN");
  lcd.setCursor(0, 1);
  lcd.print("DOWN TO LOAD");
}

void print_Pause(void){
  lcd.clear();
  lcd.print("SELECT TO RESUME");
  lcd.setCursor(0, 1);
  lcd.print("DOWN TO SAVE");
}

void flash_Error(void){
  for(int i=0;i<3;i++){
    lcd.setBacklight(RED);
    delay(250);
    lcd.setBacklight(WHITE);
    delay(250);
  }
}

void print_Load(int num){
  lcd.clear();
  lcd.setBacklight(YELLOW);
  lcd.print("Load");
  lcd.setCursor(7,0);
  lcd.print(num);
  delay(50);
}

void print_Save(int num){
  lcd.clear();
  lcd.setBacklight(YELLOW);
  lcd.print("Save");
  lcd.setCursor(7,0);
  lcd.print(num);
  delay(50);
}

void print_Q(void){
  int i=2, j=2, k;
  for(k=0; k<8; k++){
    Serial.print("Q[2][2][");
    Serial.print(k);
    Serial.print("] = ");
    Serial.println(Q[2][2][k]);
  }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

 void Create_Reward_Map(void){
  float Start_Pos1;
  float x = 0;
  for(int i=4; i>=0; i--){
     for(int j=4; j>=0; j--){
  
      Available_Actions(i, j, ACT);
      
      for(int k=0; k<Actions_Num; k++){
        
        Action_Next = Valid_Actions[k];
        Start_Pos1 = myEnc.read();
        take_Action();
        x = myEnc.read()-Start_Pos1;
        R_map[i][j][k]= x;
        Serial.print(i); Serial.print(" "); Serial.print(j); Serial.print(" "); Serial.print(Valid_Actions[k]); Serial.print(" ");
        Serial.println(x);
        
        delay(250);
        Shoulder.write(0+20*i);
        Elbow.write(0+20*j);
        delay(250);
      }
    }
  }
 printRewardMap();
}

void printRewardMap(void){
  for(int k=0;k<8;k++){
    Serial.print("R(:,:,"); Serial.print(k+1); Serial.print(") = [");
    for(int i=0; i<5; i++){
      for(int j=0; j<5; j++){
        Serial.print(" ");
        Serial.print(R_map[i][j][k]);
      }
    Serial.print(";");
    }
    Serial.println(" ];");
  }
  Shoulder.write(0+20*4);
  Elbow.write(0+20*4);
 while(1);

}

void Step_Through(void){
  int i = 4;
  int j = 4;
  Shoulder.write(0+20*i);
  Elbow.write(0+20*j);
  delay(250);
  while(1){
    uint8_t buttons = lcd.readButtons();
      if (buttons) {
        if (buttons & BUTTON_UP) i++;
        if (buttons & BUTTON_DOWN) i--;
        if (buttons & BUTTON_LEFT) j--;
        if (buttons & BUTTON_RIGHT) j++;
        
        if(i>4){ i=4; flash_Error(); }
        if(i<0){ i=0; flash_Error(); }
        if(j>4){ j=4; flash_Error(); }
        if(j<0){ j=0; flash_Error(); }
        
        lcd.clear(); lcd.setCursor(0,0); lcd.print(i); lcd.setCursor(3,0); lcd.print(j);
        Shoulder.write(0+20*i);
        Elbow.write(0+20*j);
        delay(250);
     }
  }
}

