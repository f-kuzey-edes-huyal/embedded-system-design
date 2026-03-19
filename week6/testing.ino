#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Press remote button...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();
  }
}
