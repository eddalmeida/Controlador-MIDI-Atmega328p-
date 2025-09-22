
#include <Arduino.h>
#include <Keypad.h>
#include <MIDI.h>

// ===================== CONFIGURAÇÃO MIDI =====================
MIDI_CREATE_DEFAULT_INSTANCE();

// ===================== CONFIGURAÇÃO TECLADO 3x3 =====================
const byte ROWS = 3; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
byte rowPins[ROWS] = {2, 3, 4}; // Linhas conectadas ao PD2, PD3, PD4
byte colPins[COLS] = {5, 6, 7}; // Colunas conectadas ao PD5, PD6, PD7

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Mapear cada tecla para uma nota MIDI
byte keyNotes[9] = {60, 61, 62, 63, 64, 65, 66, 67, 68};

// ===================== POTENCIÔMETROS =====================
const byte potPins[3] = {A0, A1, A2}; // PC0, PC1, PC2
const byte potCC[3] = {20, 21, 22};   // Mensagens CC
byte lastPotValue[3] = {0, 0, 0};

// Estado das teclas (para Note On/Off contínuo)
bool keyState[9] = {false};

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI); // Canal 1
  Serial.begin(31250);           // UART MIDI
}

// ===================== LOOP PRINCIPAL =====================
void loop() {
  // ===== LEITURA MATRIZ =====
  for (byte r = 0; r < ROWS; r++) {
    for (byte c = 0; c < COLS; c++) {
      char keyChar = keys[r][c];
      int index = keyChar - '1';
      if (keypad.isPressed(keyChar)) {
        if (!keyState[index]) {            // Se não estava pressionada antes
          MIDI.sendNoteOn(keyNotes[index], 127, 1);
          keyState[index] = true;
        }
      } else {
        if (keyState[index]) {             // Se foi solta
          MIDI.sendNoteOff(keyNotes[index], 0, 1);
          keyState[index] = false;
        }
      }
    }
  }

  // ===== LEITURA POTENCIÔMETROS =====
  for (byte i = 0; i < 3; i++) {
    int val = analogRead(potPins[i]);       // 0-1023
    byte midiVal = val >> 3;                // 0-127
    if (midiVal != lastPotValue[i]) {      // envia somente se mudou
      MIDI.sendControlChange(potCC[i], midiVal, 1);
      lastPotValue[i] = midiVal;
    }
  }

  delay(5); // Pequena pausa para estabilizar leitura
}
