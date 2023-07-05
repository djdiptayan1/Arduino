int relay1 = 2;
int relay2 = 3;
int relay3 = 4;
int relay4 = 5;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(relay1, HIGH);
  Serial.println("RELAY 1 HIGH");
  delay(1000);
  digitalWrite(relay1, LOW);
  Serial.println("RELAY 1 LOW");
  delay(1000);

  digitalWrite(relay2, HIGH);
  Serial.println("RELAY 2 HIGH");
  delay(1000);
  digitalWrite(relay2, LOW);
  Serial.println("RELAY 2 LOW");
  delay(1000);

  digitalWrite(relay3, HIGH);
  Serial.println("RELAY 3 HIGH");
  delay(1000);
  digitalWrite(relay3, LOW);
  Serial.println("RELAY 3 LOW");
  delay(1000);

  digitalWrite(relay4, HIGH);
  Serial.println("RELAY 4 HIGH");
  delay(1000);
  digitalWrite(relay4, LOW);
  delay(1000);
}
