#include <Servo.h>

// Create servo objects
// twelve servos max
Servo pinionServo;
Servo leftKeyServo;
Servo centerKeyServo;
Servo rightKeyServo;

int pos = 0;    // variable to store the servo position

void setup() {
  pinionServo.attach(9);
  centerKeyServo.attach(10);
}

void loop() {
  centerKeyServo.write(45); //45
  const int startPos = 0;
  const int endPosAngle = 180;
  const int endPos = map(endPosAngle, 0, 270, 0, 180);
  const int del = 20;

  for (pos = startPos; pos <= endPos; pos += 1) {
    // in steps of 1 degree
    pinionServo.write(pos); 
    delay(del); 
  }
  delay(1500);
  for (pos = endPos; pos >= startPos; pos -= 1) { 
    pinionServo.write(pos);  
    delay(del); 
  }
  delay(1500);
}