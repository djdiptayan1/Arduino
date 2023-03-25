#define gas 13
float value =0.00;
void setup() {
  Serial.begin(9600);
  pinMode(gas, INPUT);
}
void loop() {
  value = analogRead(gas);
  Serial.println(value);
}
