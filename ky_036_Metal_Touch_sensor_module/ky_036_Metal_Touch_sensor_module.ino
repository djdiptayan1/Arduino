int led = 13;
int val;
int sensorpin = 9;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensorpin, INPUT);
}

void loop() {
  if (digitalRead(sensorpin) == HIGH) {
    Serial.println("TOUCHED");
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}