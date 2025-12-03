#include <Servo.h>
#include <ctype.h>

struct KeyMapEntry {
  char c;
  int keyIndex;
};

// Array that maps char to its corresponding key index on typewriter
int charToKeyMap[96];

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
  charToKeyMap['B'] = 20; // 20 // left end 
  charToKeyMap['Y'] = 21; // 21 // right start

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
  charToKeyMap['+'] = 43; // 43 // right end
  charToKeyMap['='] = 43;
}

// Get a char's corresponding key index
int getKeyIndex(char c) {
  // Convert to upper case
  Serial.print("Getting key index of ");
  Serial.println(c);
  char upperChar = toupper(c);
  Serial.print("upper char: ");
  Serial.println(upperChar);
  int charAscii = (int) upperChar;
  Serial.print("char ascii: ");
  Serial.println(charAscii);
  return charToKeyMap[(int) upperChar];
}

// Get angle for pinion servo given key index
int getPinionAngle(int keyIndex, String fingerType) {
  if (fingerType == "left") {
    // Left finger
    // key 0 -> 170??deg
    // key 20 -> 0deg
    return map(keyIndex, 0, 20, 70, 0);
  } else {
    // Assume right finger
    // key 21 -> 180deg
    // key 43 -> 0deg
    return map(keyIndex, 21, 43, 180, 0) - 2;
  }
}

// Convert from 0 - 270deg range to 0 - 180deg
int convertPinionAngleToRange(int initAngle) {
  return map(initAngle, 0, 270, 0, 190);
}

// Create servo objects
// twelve servos max
Servo pinionServo; // 3
Servo returnFinger; // 5
Servo spaceFinger; // 6
Servo leftFinger; // 9
Servo rightFinger; // 10

//String buff = "buy*our*furry*groin*jug**you*fool";
//String buff = "   rfvtgbyhnujmik,ol";
String buff = "y & * ( )_+";
//String buff = "+++_hi \n";
//String buff = "buy*our*furry*groin*jug**you*fool";
//String buff = "***oh*my*gout*loin**glub*glub***";
//String buff = "big*oily*joint*gun";
int pinionPos = convertPinionAngleToRange(0); // current pinion servo position
const int pinionDelay = 10; // delay for incremental pinion movement 
int leftFingerStartPos = 0; // starting angle
int leftFingerEndPos = 45; // target angle for hitting key 
int rightFingerStartPos = 45; // starting angle
int rightFingerEndPos = 0; // target angle for hitting key 
int spaceFingerStartPos = 15;
int spaceFingerEndPos = 70;
int returnFingerStartPos = 0; 
int returnFingerEndPos = 45;
const int fingerDelay = 3; // delay for key trigger servos

// Move given finger to trigger key
void pressKey(Servo finger, int fingerStartPos, int fingerEndPos) {
  // Keep track of current finger angle
  int currPos = fingerStartPos;

  // Move to end angle
  while (currPos != fingerEndPos) {
    // in steps of 1 degree
    if (currPos > fingerEndPos) {
      currPos--;
    } else {
      currPos++;
    }

    // Update finger servo
    finger.write(currPos);
    delay(fingerDelay); 
  }

  // Revert to start angle
  while (currPos != fingerStartPos) {
    // in steps of 1 degree
    if (currPos > fingerStartPos) {
      currPos--;
    } else {
      currPos++;
    }

    // Update finger servo
    finger.write(currPos);
    delay(fingerDelay); 
  }
}

void setup() {
  Serial.begin(9600);

  pinionServo.attach(3); // TODO: update wiring on board
  returnFinger.attach(5);
  spaceFinger.attach(6);
  leftFinger.attach(9);
  rightFinger.attach(10);

  pinionServo.write(pinionPos);
  returnFinger.write(returnFingerStartPos);
  spaceFinger.write(spaceFingerStartPos);
  leftFinger.write(leftFingerStartPos);
  rightFinger.write(rightFingerStartPos);

  initKeyMap();
  Serial.println(buff);
}

void loop() {
  Serial.println(buff);
  /*pressKey(rightFinger);
  delay(3000);*/
  for (int i = 0; i < buff.length(); i++) {
    // Calculate key index and pinion angle based on char
    char c = buff[i];
    if (c == '\n') {
      // Trigger return carriage 
      pressKey(returnFinger, returnFingerStartPos, returnFingerEndPos);
      delay(1500);
    } else if (c == ' ') {
      // Trigger space key 
      pressKey(spaceFinger, spaceFingerStartPos, spaceFingerEndPos);
      delay(1500);
    } else {
      // Trigger key on keyboard 

      // Determine which finger to use
      String fingerType = "left";
      if (keyIndex > 20) {
        fingerType = "right";
      }

      // Get pinion angle from char
      int keyIndex = getKeyIndex(c);
      int pinionAngle = getPinionAngle(keyIndex, fingerType);
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
      delay(500);

      // Trigger finger servo to press key
      if (fingerType == "left") {
        pressKey(leftFinger, leftFingerStartPos, leftFingerEndPos);
      } else {
        pressKey(rightFinger, rightFingerStartPos, rightFingerEndPos);
      }
      delay(1500);
    }
  }
}