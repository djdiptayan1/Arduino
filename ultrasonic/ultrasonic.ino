double duration;
double distance;
void setup() {
  pinMode(9,OUTPUT);
  pinMode(8,INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(9,LOW);
  delayMicroseconds(2);
  digitalWrite(9,HIGH);
  delayMicroseconds(10);
  digitalWrite(9,LOW);

  duration=pulseIn(8,HIGH);
  distance=(duration*0.034)/2;
  Serial.print("distance ");
  Serial.print(distance);
  Serial.println();

}
