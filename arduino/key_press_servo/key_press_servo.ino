#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

const int ledPin = 11;    // the number of the LED pin

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object

  // set initial LED state
  digitalWrite(ledPin, HIGH);
}

void loop() {
  const int startPos = 45;
  const int endPos = 0;
  const int del = 5;

  for (pos = startPos; pos >= endPos; pos--) {
    // in steps of 1 degree
    myservo.write(pos); 
    delay(del); 
  }
  for (pos = endPos; pos <= startPos; pos++) { 
    myservo.write(pos);  
    delay(del); 
  }
  delay(1500);
}