double duration;
double distance;
int echo = A1;
int trig = A0;
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration * 0.034) / 2;
  Serial.print("distance ");
  Serial.print(distance);
  Serial.println();
  delay(100);
}
