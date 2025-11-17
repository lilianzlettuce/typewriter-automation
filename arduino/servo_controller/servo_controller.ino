#include <Servo.h>
#include <ctype.h>

struct KeyMapEntry {
  char c;
  int keyIndex;
};

// Array that maps char to its corresponding key index on typewriter
int charToKeyMap[90];

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
  charToKeyMap[')'] = 35; // 35
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

// Create servo objects
// twelve servos max
Servo pinionServo;
Servo leftKeyServo;
Servo centerKeyServo;
Servo rightKeyServo;

String buff = "BYTR";
int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);

  pinionServo.attach(9);
  centerKeyServo.attach(10);

  initKeyMap();
}

void loop() {
  centerKeyServo.write(45);

  const int startPos = 0;
  const int endPosAngle = 180;
  const int endPos = map(endPosAngle, 0, 270, 0, 180);
  const int del = 20;


  pinionServo.write(endPos);

  for (pos = startPos; pos <= endPos; pos += 1) {
    // in steps of 1 degree
    //pinionServo.write(pos); 
    delay(del); 
  }
  delay(1500);
  for (pos = endPos; pos >= startPos; pos -= 1) { 
    //pinionServo.write(pos);  
    delay(del); 
  }
  delay(1500);

  for (int i = 0; i < buff.length(); i++) {
    int keyIndex = getKeyIndex(buff[i]);
    Serial.println(keyIndex);
  }
}