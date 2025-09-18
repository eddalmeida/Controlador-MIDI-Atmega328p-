
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
                                                                     
Keypad keypad = Keypad(makeKeymap(tec), rowPins, colPins, linhas, colunas);
 
                                                                     
/*---------------------------------------------------------------------*/


/*--------------------------MAP HARDWARE--------------------------------*/
void setup() {                                                        
  Serial.begin(31250);                                                
}                                                                      
/*----------------------------------------------------------------------*/



unsigned int scanTEC(int key);
void statusMIDI(unsigned int status, unsigned int key);
void printMIDI(byte status, byte data1, byte data2);



void loop() 
{ 
  scanTEC(keypad.getKey());

}


unsigned int scanTEC(int key)
{
  byte note = 0;

  if (key) {
    note = 60 + (key - '0');   // calcula a nota só quando existe tecla
  }

  if (keypad.getState() == PRESSED && key) {
    statusMIDI(1, note);    
  }

  if (keypad.getState() == RELEASED && key) {
    statusMIDI(0, note);     
  }
}



void printMIDI(byte status, byte data1, byte data2) 
{
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}

void statusMIDI(unsigned status, unsigned int tec)
{
  if(status == 1){ 
      printMIDI(0x90, tec, 127);
  }

  if (status == 0)
  {
    printMIDI(0x80, tec, 0);
  }
  
}