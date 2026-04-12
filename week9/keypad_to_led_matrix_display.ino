#include <Keypad.h>
#include <LedControl.h>

// MAX7219 pins: DIN, CLK, CS, number of devices
LedControl lc = LedControl(12, 11, 10, 1);

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// 8x8 patterns
byte char1[8] = {B00011000, B00111000, B00011000, B00011000, B00011000, B00011000, B00011000, B00111100};
byte char2[8] = {B00111100, B01100110, B00000110, B00001100, B00011000, B00110000, B01100000, B01111110};
byte char3[8] = {B00111100, B01100110, B00000110, B00011100, B00000110, B00000110, B01100110, B00111100};
byte char4[8] = {B00001100, B00011100, B00101100, B01001100, B01111110, B00001100, B00001100, B00001100};
byte char5[8] = {B01111110, B01100000, B01111100, B00000110, B00000110, B00000110, B01100110, B00111100};
byte char6[8] = {B00111100, B01100110, B01100000, B01111100, B01100110, B01100110, B01100110, B00111100};
byte char7[8] = {B01111110, B00000110, B00001100, B00011000, B00110000, B00110000, B00110000, B00110000};
byte char8[8] = {B00111100, B01100110, B01100110, B00111100, B01100110, B01100110, B01100110, B00111100};
byte char9[8] = {B00111100, B01100110, B01100110, B00111110, B00000110, B00000110, B01100110, B00111100};
byte char0[8] = {B00111100, B01100110, B01101110, B01110110, B01100110, B01100110, B01100110, B00111100};

byte charA[8] = {B00011000, B00111100, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110};
byte charB[8] = {B01111100, B01100110, B01100110, B01111100, B01100110, B01100110, B01100110, B01111100};
byte charC[8] = {B00111100, B01100110, B01100000, B01100000, B01100000, B01100000, B01100110, B00111100};
byte charD[8] = {B01111000, B01101100, B01100110, B01100110, B01100110, B01100110, B01101100, B01111000};

byte hashChar[8] = {B00100100, B00100100, B11111111, B00100100, B11111111, B00100100, B00100100, B00000000};

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  Serial.println("Press a keypad button...");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);

    switch (key) {
      case '1': drawCharacter(char1); break;
      case '2': drawCharacter(char2); break;
      case '3': drawCharacter(char3); break;
      case '4': drawCharacter(char4); break;
      case '5': drawCharacter(char5); break;
      case '6': drawCharacter(char6); break;
      case '7': drawCharacter(char7); break;
      case '8': drawCharacter(char8); break;
      case '9': drawCharacter(char9); break;
      case '0': drawCharacter(char0); break;
      case 'A': drawCharacter(charA); break;
      case 'B': drawCharacter(charB); break;
      case 'C': drawCharacter(charC); break;
      case 'D': drawCharacter(charD); break;
      case '#': drawCharacter(hashChar); break;
      case '*': lc.clearDisplay(0); break;
    }
  }
}

byte reverseByte(byte b) {
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}

void drawCharacter(const byte character[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, reverseByte(character[row]));
  }
}