// ===== VERY SENSITIVE TOUCH COLOR DEMO =====
// KY-013 + KY-016
// Easy visible color change when you touch the sensor

const byte TEMP_PIN = A0;

// RGB pins
const byte RED_PIN   = 11;
const byte GREEN_PIN = 9;
const byte BLUE_PIN  = 10;

// true for common cathode, false for common anode
const bool COMMON_CATHODE = true;

// If touching gives colder colors, change to true
const bool INVERT_TEMP_DIRECTION = false;

// Make touch effect much stronger
const float TOUCH_GAIN = 20.0;

// Small neutral area
const int NEUTRAL_BAND = 1;

// Baseline room value
float roomValue = 0;
float filteredRaw = 0;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);
  delay(500);

  // quick LED test
  setRGB(255, 0, 0); delay(300);
  setRGB(0, 255, 0); delay(300);
  setRGB(0, 0, 255); delay(300);
  setRGB(0, 0, 0);   delay(300);

  // Read room baseline once at startup
  roomValue = calibrateRoomValue();
  filteredRaw = roomValue;

  Serial.print("Room baseline = ");
  Serial.println(roomValue);
}

void loop() {
  int raw = readAverageAnalog();

  // faster response
  filteredRaw = 0.50 * raw + 0.50 * filteredRaw;

  float diff = filteredRaw - roomValue;

  if (INVERT_TEMP_DIRECTION) {
    diff = -diff;
  }

  // amplify small changes
  float boosted = diff * TOUCH_GAIN;

  // limit
  if (boosted > 255) boosted = 255;
  if (boosted < -255) boosted = -255;

  int r, g, b;
  boostedToColor(boosted, r, g, b);
  setRGB(r, g, b);

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  Filtered: ");
  Serial.print(filteredRaw, 1);
  Serial.print("  Diff: ");
  Serial.print(diff, 2);
  Serial.print("  Boosted: ");
  Serial.print(boosted, 1);
  Serial.print("  RGB(");
  Serial.print(r);
  Serial.print(",");
  Serial.print(g);
  Serial.print(",");
  Serial.print(b);
  Serial.println(")");

  delay(80);
}

float calibrateRoomValue() {
  long total = 0;
  const int count = 40;

  for (int i = 0; i < count; i++) {
    total += analogRead(TEMP_PIN);
    delay(10);
  }

  return total / float(count);
}

int readAverageAnalog() {
  long total = 0;
  const byte count = 6;

  for (byte i = 0; i < count; i++) {
    total += analogRead(TEMP_PIN);
    delay(2);
  }

  return total / count;
}

void boostedToColor(float x, int &r, int &g, int &b) {
  // near room temperature = bright green
  if (x >= -NEUTRAL_BAND && x <= NEUTRAL_BAND) {
    r = 0;
    g = 255;
    b = 0;
    return;
  }

  // warmer side: green -> yellow -> orange -> red -> magenta
  if (x > NEUTRAL_BAND) {
    if (x < 80) {
      // green -> yellow
      r = map((int)x, 0, 80, 0, 255);
      g = 255;
      b = 0;
    } else if (x < 160) {
      // yellow -> red
      r = 255;
      g = map((int)x, 80, 160, 255, 0);
      b = 0;
    } else {
      // red -> magenta
      r = 255;
      g = 0;
      b = map((int)x, 160, 255, 0, 180);
    }
    return;
  }

  // colder side: green -> cyan -> blue -> purple
  if (x < -NEUTRAL_BAND) {
    int y = (int)(-x);

    if (y < 80) {
      // green -> cyan
      r = 0;
      g = 255;
      b = map(y, 0, 80, 0, 255);
    } else if (y < 160) {
      // cyan -> blue
      r = 0;
      g = map(y, 80, 160, 255, 0);
      b = 255;
    } else {
      // blue -> purple
      r = map(y, 160, 255, 0, 180);
      g = 0;
      b = 255;
    }
    return;
  }
}

void setRGB(int r, int g, int b) {
  if (COMMON_CATHODE) {
    analogWrite(RED_PIN, r);
    analogWrite(GREEN_PIN, g);
    analogWrite(BLUE_PIN, b);
  } else {
    analogWrite(RED_PIN, 255 - r);
    analogWrite(GREEN_PIN, 255 - g);
    analogWrite(BLUE_PIN, 255 - b);
  }
}