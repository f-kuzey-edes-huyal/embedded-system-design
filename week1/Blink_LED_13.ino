const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // LED ON
  delay(500);
  digitalWrite(ledPin, LOW);  // LED OFF
  delay(500);
}
