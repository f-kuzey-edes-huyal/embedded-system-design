const byte SOUND_PIN = 2;     
const byte GREEN_LED = 8;     
const byte RED_LED = 9;       

// Wokwi pushbutton + INPUT_PULLUP -> active LOW
// If needed on real KY-037, change to HIGH
const byte SOUND_ACTIVE = LOW;

enum SystemState {
  ARMED,
  ALERT
};

SystemState state = ARMED;

int lastReading = HIGH;
unsigned long lastTriggerTime = 0;
unsigned long alertStartTime = 0;
unsigned long lastBlinkTime = 0;

const unsigned long debounceMs = 120;
const unsigned long alertDuration = 3000;
const unsigned long blinkInterval = 200;

bool redLedState = false;

void setArmedMode() {
  state = ARMED;
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  redLedState = false;
  Serial.println("State -> ARMED");
}

void setAlertMode() {
  state = ALERT;
  alertStartTime = millis();
  lastBlinkTime = millis();
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  redLedState = true;
  Serial.println("State -> ALERT");
}

void setup() {
  pinMode(SOUND_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  Serial.begin(9600);
  setArmedMode();
}

void loop() {
  unsigned long now = millis();
  int reading = digitalRead(SOUND_PIN);

  // detect a new trigger
  if (reading == SOUND_ACTIVE && lastReading != SOUND_ACTIVE) {
    if (now - lastTriggerTime > debounceMs) {
      lastTriggerTime = now;

      if (state == ARMED) {
        setAlertMode();
      } else {
        // extend alert time if another sound comes during alert
        alertStartTime = now;
        Serial.println("Alert extended");
      }
    }
  }

  if (state == ALERT) {
    if (now - lastBlinkTime >= blinkInterval) {
      lastBlinkTime = now;
      redLedState = !redLedState;
      digitalWrite(RED_LED, redLedState);
    }

    if (now - alertStartTime >= alertDuration) {
      setArmedMode();
    }
  }

  lastReading = reading;
}