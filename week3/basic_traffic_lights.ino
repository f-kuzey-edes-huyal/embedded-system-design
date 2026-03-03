const int RED = 8;
const int YELLOW = 9;
const int GREEN = 10;






void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED, HIGH);
  delay(10000);
  digitalWrite(RED,LOW);
 
  digitalWrite(GREEN, HIGH);
  delay(10000);
  digitalWrite(GREEN, LOW);

  //YELLOW
  digitalWrite(YELLOW, HIGH);
  delay(10000);
  digitalWrite(YELLOW, LOW);

}
