
void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Press remote button...");
}

void loop() {
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println("Unknown or noisy signal");
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    } else {
      IrReceiver.printIRResultShort(&Serial);
      Serial.print("Command: 0x");
      Serial.println(IrReceiver.decodedIRData.command, HEX);
    }
    IrReceiver.resume();
    Serial.println();
  }
}