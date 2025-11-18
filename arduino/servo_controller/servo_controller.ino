#include <Servo.h>
#include <ctype.h>

struct KeyMapEntry {
  char c;
  int keyIndex;
};

// Array that maps char to its corresponding key index on typewriter
int charToKeyMap[95];

// Initialize the above key map
// Use ascii value for each char as its index in map
void initKeyMap() {
  charToKeyMap['!'] = 0; // 0
  charToKeyMap['1'] = 0;
  charToKeyMap['Q'] = 1; // 1
  charToKeyMap['A'] = 2; // 2
  charToKeyMap['@'] = 3; // 3
  charToKeyMap['2'] = 3;
  charToKeyMap['Z'] = 4; // 4
  charToKeyMap['W'] = 5; // 5
  charToKeyMap['S'] = 6; // 6
  charToKeyMap['#'] = 7; // 7
  charToKeyMap['3'] = 7;
  charToKeyMap['X'] = 8; // 8
  charToKeyMap['E'] = 9; // 9
  charToKeyMap['D'] = 10; // 10

  charToKeyMap['$'] = 11; // 11
  charToKeyMap['4'] = 11;
  charToKeyMap['C'] = 12; // 12
  charToKeyMap['R'] = 13; // 13 // center start
  charToKeyMap['F'] = 14; // 14
  charToKeyMap['%'] = 15; // 15
  charToKeyMap['5'] = 15;
  charToKeyMap['V'] = 16; // 16
  charToKeyMap['T'] = 17; // 17
  charToKeyMap['G'] = 18; // 18
  charToKeyMap['^'] = 19; // 19
  charToKeyMap['6'] = 19;
  charToKeyMap['B'] = 20; // 20
  charToKeyMap['Y'] = 21; // 21

  charToKeyMap['H'] = 22; // 22
  charToKeyMap['&'] = 23; // 23
  charToKeyMap['7'] = 23;
  charToKeyMap['N'] = 24; // 24
  charToKeyMap['U'] = 25; // 25
  charToKeyMap['J'] = 26; // 26
  charToKeyMap['*'] = 27; // 27
  charToKeyMap['8'] = 27;
  charToKeyMap['M'] = 28; // 28
  charToKeyMap['I'] = 29; // 29
  charToKeyMap['K'] = 30; // 30
  charToKeyMap['('] = 31; // 31
  charToKeyMap['9'] = 31;
  charToKeyMap[','] = 32; // 32
  //charToKeyMap[''] = 32;

  charToKeyMap['O'] = 33; // 33
  charToKeyMap['L'] = 34; // 34
  charToKeyMap[')'] = 35; // 35 // center end
  charToKeyMap['0'] = 35;
  charToKeyMap['.'] = 36; // 36
  //charToKeyMap[''] = ;
  charToKeyMap['P'] = 37; // 37
  charToKeyMap[':'] = 38; // 38
  charToKeyMap[';'] = 38;
  charToKeyMap['_'] = 39; // 39
  charToKeyMap['-'] = 39;
  charToKeyMap['?'] = 40; // 40
  charToKeyMap['/'] = 40;
  //charToKeyMap[''] = ; // 41 fractions?
  charToKeyMap['\"'] = 42; // 42
  charToKeyMap['\''] = 42;
  charToKeyMap['+'] = 43; // 43
  charToKeyMap['='] = 43;
  //charToKeyMap[''] = ;
}

// Get a char's corresponding key index
int getKeyIndex(char c) {
  // Convert to upper case
  char upperChar = toupper(c);
  return charToKeyMap[(int) upperChar];
}

// Get angle for pinion servo given key index
int getPinionAngle(int keyIndex) {
  // Assume center for now
  // key 13 -> 180deg
  // key 35 -> 0deg
  return map(keyIndex, 13, 35, 0, 180);
}

// Convert from 0 - 270deg range to 0 - 180deg
int convertPinionAngleToRange(int initAngle) {
  return map(initAngle, 0, 270, 0, 180);
}

// Create servo objects
// twelve servos max
Servo pinionServo;
Servo leftKeyServo;
Servo centerFinger;
Servo rightKeyServo;

//String buff = "loin***";
String buff = "loin*oil*bit*hull*guy";
int pinionPos = 0;    // current pinion servo position
const int pinionDelay = 20; // delay for incremental pinion movement 
int centerFingerPos = 45;    // current pinion servo position
const int fingerDelay = 5; // delay for incremental pinion movement 

void setup() {
  Serial.begin(9600);

  pinionServo.attach(9);
  centerFinger.attach(10);

  pinionServo.write(pinionPos);
  centerFinger.write(centerFingerPos);

  initKeyMap();
  Serial.println(buff);
}

void loop() {
  Serial.println(buff);
  for (int i = 0; i < buff.length(); i++) {
    // Calculate key index and pinion angle based on char
    char c = buff[i];
    int keyIndex = getKeyIndex(c);
    int pinionAngle = getPinionAngle(keyIndex);
    Serial.print(c);
    Serial.print(": ");
    Serial.println(keyIndex);

    // Move pinion
    int nextPinionPos = convertPinionAngleToRange(pinionAngle);
    while (pinionPos != nextPinionPos) {
      // in steps of 1 degree
      if (pinionPos > nextPinionPos) {
        // Decrement if larger
        pinionPos--;
      } else {
        // Increment if smaller
        pinionPos++;
      }

      // Update pinion servo
      pinionServo.write(pinionPos);
      delay(pinionDelay); 
    }
    delay(600);

    // Move key trigger arm
    while (centerFingerPos != 0) {
      // in steps of 1 degree
      centerFingerPos--;

      // Update pinion servo
      centerFinger.write(centerFingerPos);
      delay(fingerDelay); 
    }
    while (centerFingerPos != 45) {
      // in steps of 1 degree
      centerFingerPos++;

      // Update pinion servo
      centerFinger.write(centerFingerPos);
      delay(fingerDelay); 
    }
    delay(1500);
  }
}