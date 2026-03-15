#include <math.h>

// ===== Pins =====
const byte TEMP_PIN  = A0;
const byte RED_PIN   = 9;
const byte GREEN_PIN = 10;
const byte BLUE_PIN  = 11;

// ===== Wokwi NTC =====
const float BETA = 3950.0;

// ===== RGB LED =====
// Wokwi default RGB LED is common anode
const bool COMMON_ANODE = true;

// ===== Binary color threshold =====
// Below this -> blue
// At or above this -> red
const float RED_THRESHOLD = 30.0;

// ===== Filtering =====
const byte SAMPLE_COUNT = 10;
const float FILTER_ALPHA = 0.25;
float filteredTemp = NAN;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  float tempC = readTemperatureC();

  if (isnan(tempC)) {
    Serial.println("Sensor error");
    setRGB(255, 0, 255); // magenta
    delay(300);
    return;
  }

  if (isnan(filteredTemp)) {
    filteredTemp = tempC;
  } else {
    filteredTemp = FILTER_ALPHA * tempC + (1.0 - FILTER_ALPHA) * filteredTemp;
  }

  int r, g, b;
  if (filteredTemp >= RED_THRESHOLD) {
    r = 255; g = 0; b = 0;   // red
  } else {
    r = 0;   g = 0; b = 255; // blue
  }

  setRGB(r, g, b);

  Serial.print("ADC: ");
  Serial.print(readRawADC());
  Serial.print("   Temp: ");
  Serial.print(filteredTemp, 2);
  Serial.print(" C   RGB(");
  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.print(b);
  Serial.println(")");

  delay(200);
}

int readRawADC() {
  long total = 0;
  for (byte i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(TEMP_PIN);
    delay(3);
  }
  return (int)(total / SAMPLE_COUNT);
}

float readTemperatureC() {
  int analogValue = readRawADC();

  if (analogValue <= 0 || analogValue >= 1023) {
    return NAN;
  }

  float celsius =
    1.0 / (log(1.0 / (1023.0 / analogValue - 1.0)) / BETA + 1.0 / 298.15) - 273.15;

  return celsius;
}

void setRGB(int r, int g, int b) {
  if (COMMON_ANODE) {
    analogWrite(RED_PIN,   255 - r);
    analogWrite(GREEN_PIN, 255 - g);
    analogWrite(BLUE_PIN,  255 - b);
  } else {
    analogWrite(RED_PIN,   r);
    analogWrite(GREEN_PIN, g);
    analogWrite(BLUE_PIN,  b);
  }
}