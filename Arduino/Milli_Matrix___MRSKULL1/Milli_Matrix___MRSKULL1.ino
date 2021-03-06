#include "milliMATRIX_Definitions.h"

const int modeButton = 0;

// pin[xx] on led matrix connected to nn on Arduino
// (-1 is dummy to make array start at pos 1)
int pins[17]= {-1, 7, 17, 15, 16, 14, 11, 3,
                2, 4, 12, 6, 8, 9, 10, 5, 13};

// col[xx] of leds = pin yy on led matrix
int cols[8] = {pins[13], pins[3], pins[4], pins[10],
               pins[06], pins[11], pins[15], pins[16]};

// row[xx] of leds = pin yy on led matrix
int rows[8] = {pins[9], pins[14], pins[8], pins[12], 
               pins[1], pins[7], pins[2], pins[5]};

int frameCount = 0;
int patternCount = 0;

byte col = 0;
byte row = 0;
byte mode = 0;
byte randPattern;
byte pattern[14][8][8] = {MRSKULL0, MRSKULL1, MRSKULL2, MRSKULL3, 
                          MRSKULL4, MRSKULL5, MRSKULL6, MRSKULL7,
                          MRSKULL8, MRSKULL9, INVADER0, INVADER1,
                          INVADER2, INVADER3};

void setup() {
  // set the mode select button pin as an input
  pinMode(modeButton, INPUT);
  
  // sets the pins as output
  for (int i = 1; i <= 16; i++) {
    pinMode(pins[i], OUTPUT);
  }  
  // set up cols and rows
  for (int i = 1; i <= 8; i++) {
    digitalWrite(cols[i - 1], LOW);
  }
  for (int i = 1; i <= 8; i++) {
    digitalWrite(rows[i - 1], HIGH);
  }
  // seed the random number with noise on an unconnected pin
  randomSeed(analogRead(0));
}

void loop() {
  if (digitalRead(modeButton) == HIGH) {
    mode++;
    if (mode > 3) {
      mode = 0;
    }
    frameCount = 0;
    delay(150);
  }
  
  if (mode == 0){
    randSkulls();
  }
  else if (mode == 1) {
    nomnomSkull();
  }
  else if (mode == 2) {
    spaceInvader1();
  }
  
  else if (mode == 3) {
    spaceInvader2();
  }
  
  refreshFrame();
}

void refreshFrame() {
  for (int i = 0; i < 8; i++) {      // loop to scan thru columns
    digitalWrite(cols[i], HIGH);     // enable column 'i'
    for (int j = 0; j < 8; j++) {    // loop to scan thru rows
      if (pattern[patternCount][i][j] == 1) {    // reference the predefined pattern
        digitalWrite(rows[j], LOW);    // enable row 'j'. turn on the LED at column 'i' and row 'j'
        delayMicroseconds(100);         // leave the LED on for 10 microseconds
        digitalWrite(rows[j], HIGH);   // turn the LED off
      } 
/*      else {
        delayMicroseconds(1);
      }
*/      
    }
    digitalWrite(cols[i], LOW);
  }
}

void nomnomSkull() {
  ++frameCount;
  if (frameCount == 1) {
    patternCount = 2;
  }
  else if (frameCount == 100) {
    patternCount = 3;
  }
  else if (frameCount == 200) {
    patternCount = 2;
    frameCount = 0;
  }
}

void spaceInvader1() {
  ++frameCount;
  if (frameCount == 1) {
    patternCount = 11;
  }
  if (frameCount == 100) {
    patternCount = 10;
  }
  if (frameCount == 200) {
    patternCount = 11;
    frameCount = 0;
  }
}

void spaceInvader2() {
  ++frameCount;
  if (frameCount == 1) {
    patternCount = 12;
  }
  if (frameCount == 100) {
    patternCount = 13;
  }
  if (frameCount == 200) {
    patternCount = 12;
    frameCount = 0;
  }
}

void randSkulls() {
  ++frameCount;
  if (frameCount == 1) {
      patternCount = 0;
  }
  else if (frameCount == 700) {
      randPattern = random(10);
      patternCount = randPattern;
    }
  else if (frameCount == 900) {
    patternCount = 0;
    frameCount = 0;
  }
}

