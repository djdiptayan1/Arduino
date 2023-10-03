int relay = 2;
int relay2 = 3;

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay, HIGH);
  digitalWrite(relay2, HIGH);
  Serial.println("HIGH");
  delay(1000);
  digitalWrite(relay, LOW);
  digitalWrite(relay2, LOW);
  Serial.println("LOW");
  delay(1000);
}
