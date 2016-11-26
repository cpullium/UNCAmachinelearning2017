#include "Servo.h"


Servo shoulder;
Servo elbow;
void setup() {
//   put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  shoulder.attach(9);
  elbow.attach(10);
  delay(10);
  shoulder.write(60);
  elbow.write(20);
  digitalWrite(11,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  shoulder.write(60);
  elbow.write(20);
  delay(500);
  shoulder.write(40);
  elbow.write(20);
  delay(500);
  shoulder.write(40);
  elbow.write(40);
  delay(500);
}
