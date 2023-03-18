#define INP 9

void setup() {
  pinMode(INP, INPUT);
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(INP);
  if (val==LOW) {
  Serial.println("NO OBJECT");
  delay(200);
  }
  else {
  Serial.println("OBJECT DETECTED");
  delay(200);
    }

}
