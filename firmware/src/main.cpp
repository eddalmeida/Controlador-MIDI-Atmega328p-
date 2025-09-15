
#include <Arduino.h>

#include <Keypad.h>

/*--------------------Configuração do teclado--------------------------*/
const byte linhas = 3; //quantidade de linhas                        
const byte colunas = 3;//quantidade de colunas                      
                                                                     
char tec[linhas][colunas] = {   //oque vai retornar do teclado       
  {'1','2','3'},                                                     
  {'4','5','6'},                                                     
  {'7','8','9'}                                                      
};                                                                   
                                                                     
                                                                     
byte rowPins[linhas] = {13, 12, 11}; //pinos da linha do teclado     
byte colPins[colunas] = {10, 9, 8};//pinos da coluba do teclado      
                                                                     
Keypad keypad = Keypad(makeKeymap(tec), rowPins, linhas, colunas);   
                                                                     
/*---------------------------------------------------------------------*/


/*--------------------------MAP HARDWARE--------------------------------*/
void setup() {                                                        
  Serial.begin(31250);                                                
}                                                                     
/*----------------------------------------------------------------------*/

void sendMIDI(byte status, byte data1, byte data2)



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


void sendMIDI(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}