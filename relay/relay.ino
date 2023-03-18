const int relay = 5;

void setup() {
  pinMode(relay, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay, HIGH);
  for (int i = 0; i < 100; i++) {
    if (i % 5 == 0) {
      Serial.println(i);
      digitalWrite(relay, LOW);
      delay(5000);
      digitalWrite(relay, HIGH);
      delay(5000);
    }
    else
    digitalWrite(relay, HIGH);
  }
}
