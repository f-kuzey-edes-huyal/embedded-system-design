const int RED = 8;
const int YELLOW = 9;
const int GREEN = 10;
const int BUTTON = A2;

unsigned long previousMillis = 0;
unsigned long greenStartTime = 0;

const unsigned long RED_TIME = 8000;
const unsigned long GREEN_TIME = 8000;
const unsigned long YELLOW_TIME = 3000;
const unsigned long PEDESTRIAN_RED_TIME = 6000;
const unsigned long MIN_GREEN_TIME = 3000;

bool pedestrianRequest = false;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

enum State {
  RED_STATE,
  GREEN_STATE,
  YELLOW_STATE,
  PEDESTRIAN_RED_STATE
};

State currentState = RED_STATE;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  
  setState(RED_STATE);
}

void loop() {

  unsigned long currentMillis = millis();
  readButton(currentMillis);

  switch (currentState) {

    case RED_STATE:
      if (currentMillis - previousMillis >= RED_TIME) {
        changeState(GREEN_STATE);
        greenStartTime = currentMillis;
      }
      break;

    case GREEN_STATE:
      if (pedestrianRequest && 
          currentMillis - greenStartTime >= MIN_GREEN_TIME) {
        changeState(YELLOW_STATE);
      }
      else if (currentMillis - previousMillis >= GREEN_TIME) {
        changeState(YELLOW_STATE);
      }
      break;

    case YELLOW_STATE:
      if (currentMillis - previousMillis >= YELLOW_TIME) {
        if (pedestrianRequest) {
          changeState(PEDESTRIAN_RED_STATE);
        } else {
          changeState(RED_STATE);
        }
      }
      break;

    case PEDESTRIAN_RED_STATE:
      if (currentMillis - previousMillis >= PEDESTRIAN_RED_TIME) {
        pedestrianRequest = false;
        changeState(RED_STATE);
      }
      break;
  }
}

void changeState(State newState) {
  previousMillis = millis();
  currentState = newState;
  setState(newState);
}

void setState(State state) {
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);

  switch (state) {
    case RED_STATE:
      digitalWrite(RED, HIGH);
      break;
    case GREEN_STATE:
      digitalWrite(GREEN, HIGH);
      break;
    case YELLOW_STATE:
      digitalWrite(YELLOW, HIGH);
      break;
    case PEDESTRIAN_RED_STATE:
      digitalWrite(RED, HIGH);
      break;
  }
}

void readButton(unsigned long currentMillis) {
  if (digitalRead(BUTTON) == LOW) {
    if (currentMillis - lastDebounceTime > debounceDelay) {
      pedestrianRequest = true;
      lastDebounceTime = currentMillis;
    }
  }
}
