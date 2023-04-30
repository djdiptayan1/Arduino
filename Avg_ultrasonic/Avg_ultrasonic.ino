const int trig = A0 ;
const int echo = A1;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  int measurements = 10;
  long totalDistance = 0;

  for (int i = 0; i < measurements; i++) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;

    totalDistance += distance;
  }

  int averageDistance = totalDistance / measurements;
  Serial.print("Average Distance: ");
  Serial.println(averageDistance);

  delay(100);
}
