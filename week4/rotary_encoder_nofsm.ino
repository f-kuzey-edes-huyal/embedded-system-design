const int CLK = 2;
const int DT  = 3;
const int SW  = 4;
const int LED = 8;

int counter = 0;
int lastCLK;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  lastCLK = digitalRead(CLK);
}

void loop() {
  int currentCLK = digitalRead(CLK);

  // Read encoder rotation
  if (currentCLK != lastCLK && currentCLK == HIGH) {
    if (digitalRead(DT) != currentCLK) {
      counter++;
    } else {
      counter--;
    }

    if (counter < 0) counter = 0;
    if (counter > 10) counter = 10;

    Serial.print("Counter: ");
    Serial.println(counter);
  }

  lastCLK = currentCLK;

  // Reset with button press
  if (digitalRead(SW) == LOW) {
    counter = 0;
    Serial.println("Reset");
    delay(200);
  }

  // Direct control
  if (counter >= 5) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}