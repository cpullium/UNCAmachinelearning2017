#include "Arduino.h"
extern int led;

void blinkandPause(void){
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(250);               // wait for a second
}