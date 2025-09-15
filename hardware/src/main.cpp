#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 3; 
const byte COLS = 3; 

char nineKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};

byte rowPins[ROWS] = {13, 12, 11}; 
byte colPins[COLS] = {10, 9, 8};

Keypad keypad = Keypad(makeKeymap(nineKeys), rowPins, colPins, ROWS, COLS);


void sendMIDI(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

void setup() {
  Serial.begin(31250); 
}

void loop() {
  char key = keypad.getKey();  
  
  if (key) {
   
    if (keypad.getState() == PRESSED) {
      byte note = 60 + (key - '0');  
      sendMIDI(0x90, note, 127);     
    }

    
    if (keypad.getState() == RELEASED) {
      byte note = 60 + (key - '0');
      sendMIDI(0x80, note, 0);       
    }
  }
}