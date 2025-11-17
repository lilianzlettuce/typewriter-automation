#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  const int startPos = 0;
  const int endPosAngle = 180;
  const int endPos = map(endPosAngle, 0, 270, 0, 180);
  const int del = 20;

  for (pos = startPos; pos <= endPos; pos += 1) {
    // in steps of 1 degree
    myservo.write(pos); 
    delay(del); 
  }
  delay(1500);
  for (pos = endPos; pos >= startPos; pos -= 1) { 
    myservo.write(pos);  
    delay(del); 
  }
  delay(1500);
}