#include <IRremote.hpp>

const int IR_RECEIVE_PIN = 2;
const int LED_PIN = 8;

// Change this to your own button code from Serial Monitor
const uint8_t TOGGLE_CMD = 0x13;

bool ledState = false;
unsigned long lastPressTime = 0;
const unsigned long cooldown = 300;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    uint8_t command = IrReceiver.decodedIRData.command;
    IrReceiver.resume();

    if (command == TOGGLE_CMD) {
      unsigned long now = millis();

      if (now - lastPressTime > cooldown) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        lastPressTime = now;
      }
    }
  }
}
