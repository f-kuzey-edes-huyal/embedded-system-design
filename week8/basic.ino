const byte SOUND_PIN = 2;     // KY-037 DO or Wokwi pushbutton
const byte GREEN_LED = 8;
const byte RED_LED = 9;

// For Wokwi pushbutton with INPUT_PULLUP, pressed = LOW
// If your real KY-037 is active HIGH, change this to HIGH
const byte SOUND_ACTIVE = LOW;

unsigned long alertStart = 0;
bool alertActive = false;
int lastReading = HIGH;

void setup() {
  pinMode(SOUND_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(SOUND_PIN);

  // rising event in logic sense: idle -> active
  if (reading == SOUND_ACTIVE && lastReading != SOUND_ACTIVE) {
    alertActive = true;
    alertStart = millis();
    Serial.println("Sound detected");
  }

  if (alertActive) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    if (millis() - alertStart >= 1000) {
      alertActive = false;
    }
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }

  lastReading = reading;
}