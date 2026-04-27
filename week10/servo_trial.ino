#include <Servo.h>

Servo myServo;

// Pin definitions
const int potPin = A0;
const int servoPin = 9;
const int buttonPin = 2;
const int ledPin = 6;

// Servo control
int servoAngle = 90;
int targetAngle = 90;
int lastServoAngle = 90;

// Filtering
float filteredPotValue = 0;
const float alpha = 0.15;   // Smaller value = smoother signal

// Deadband
const int deadband = 2;     // Ignore changes smaller than 2 degrees

// Mode control
bool manualMode = true;

// Button debounce
bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

// Timing
unsigned long lastControlTime = 0;
const unsigned long controlInterval = 20;

// Sweep mode variables
int sweepAngle = 0;
int sweepDirection = 1;

// Safety zone
const int dangerAngle = 140;

void setup() {
  myServo.attach(servoPin);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  myServo.write(servoAngle);

  Serial.println("Smart Servo Controller Started");
  Serial.println("Mode: Manual");
}

void loop() {
  handleButton();

  unsigned long currentTime = millis();

  if (currentTime - lastControlTime >= controlInterval) {
    lastControlTime = currentTime;

    if (manualMode) {
      manualServoControl();
    } else {
      sweepServoControl();
    }

    safetyCheck();
    printStatus();
  }
}

void handleButton() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != currentButtonState) {
      currentButtonState = reading;

      if (currentButtonState == LOW) {
        manualMode = !manualMode;

        if (manualMode) {
          Serial.println("Mode changed to: Manual");
        } else {
          Serial.println("Mode changed to: Sweep");
        }
      }
    }
  }

  lastButtonState = reading;
}

void manualServoControl() {
  int rawPotValue = analogRead(potPin);

  filteredPotValue = alpha * rawPotValue + (1 - alpha) * filteredPotValue;

  targetAngle = map(filteredPotValue, 0, 1023, 0, 180);

  if (abs(targetAngle - lastServoAngle) >= deadband) {
    servoAngle = targetAngle;
    myServo.write(servoAngle);
    lastServoAngle = servoAngle;
  }
}

void sweepServoControl() {
  sweepAngle += sweepDirection;

  if (sweepAngle >= 180) {
    sweepAngle = 180;
    sweepDirection = -1;
  }

  if (sweepAngle <= 0) {
    sweepAngle = 0;
    sweepDirection = 1;
  }

  servoAngle = sweepAngle;
  myServo.write(servoAngle);
}

void safetyCheck() {
  if (servoAngle > dangerAngle) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void printStatus() {
  Serial.print("Mode: ");

  if (manualMode) {
    Serial.print("Manual");
  } else {
    Serial.print("Sweep");
  }

  Serial.print(" | Angle: ");
  Serial.print(servoAngle);

  Serial.print(" | Danger Zone: ");

  if (servoAngle > dangerAngle) {
    Serial.println("YES");
  } else {
    Serial.println("NO");
  }
}