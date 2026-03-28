const int GAS_SENSOR_PIN = A0;
const int BUZZER_PIN = 8;

const int CALIBRATION_SAMPLES = 50;
const int SAMPLE_COUNT = 10;
const float FILTER_ALPHA = 0.2;

int baseline = 0;
float filteredValue = 0;

int gasThresholdOffset = 80;
int hysteresis = 20;

bool alarmActive = false;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Gas detection system starting...");
  Serial.println("Calibrating sensor...");

  baseline = calibrateSensor();
  filteredValue = baseline;

  Serial.print("Baseline: ");
  Serial.println(baseline);
}

void loop() {
  int rawValue = readAveragedGasValue();
  filteredValue = FILTER_ALPHA * rawValue + (1.0 - FILTER_ALPHA) * filteredValue;

  int alarmThreshold = baseline + gasThresholdOffset;
  int resetThreshold = alarmThreshold - hysteresis;

  if (!alarmActive && filteredValue > alarmThreshold) {
    alarmActive = true;
    Serial.println("WARNING: Gas detected!");
  } 
  else if (alarmActive && filteredValue < resetThreshold) {
    alarmActive = false;
    noTone(BUZZER_PIN);
    Serial.println("Gas level back to normal.");
  }

  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print(" | Filtered: ");
  Serial.print((int)filteredValue);
  Serial.print(" | Baseline: ");
  Serial.print(baseline);
  Serial.print(" | Alarm: ");
  Serial.println(alarmActive ? "ON" : "OFF");

  if (alarmActive) {
    handleBuzzer((int)filteredValue, alarmThreshold);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(100);
}

int calibrateSensor() {
  long total = 0;
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    total += analogRead(GAS_SENSOR_PIN);
    delay(20);
  }
  return total / CALIBRATION_SAMPLES;
}

int readAveragedGasValue() {
  long total = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(GAS_SENSOR_PIN);
    delay(5);
  }
  return total / SAMPLE_COUNT;
}

void handleBuzzer(int currentValue, int threshold) {
  int excess = currentValue - threshold;
  excess = constrain(excess, 0, 400);

  // Higher gas => higher pitch
  int frequency = map(excess, 0, 400, 400, 2000);

  tone(BUZZER_PIN, frequency);
}