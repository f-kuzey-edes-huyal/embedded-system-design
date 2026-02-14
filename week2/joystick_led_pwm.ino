const int joystickX = A0;   // VRx connected to A0
const int ledPin = 9;       // PWM pin (must be ~)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(joystickX);  // 0 - 1023

  // 1) Map joystick to PWM
  int pwmValue = map(xValue, 0, 1023, 0, 255);

  // 2) Add a minimum brightness (optional but useful)
  //    This makes the LED always visible
  int minBrightness = 30;
  pwmValue = map(xValue, 0, 1023, minBrightness, 255);

  // 3) Apply a curve to make brightness changes more visible
  //    (human eyes don't see brightness linearly)
  pwmValue = (pwmValue * pwmValue) / 255;

  // Output PWM
  analogWrite(ledPin, pwmValue);

  // Serial output
  Serial.print("Joystick X: ");
  Serial.print(xValue);
  Serial.print("  PWM: ");
  Serial.println(pwmValue);

  delay(10);
}
