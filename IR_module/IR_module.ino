#define ir1 8
#define ir2 9

void setup() {
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value1=digitalRead(ir1);
  int value2=digitalRead(ir2);
  //Serial.println(value1);
  Serial.println(value2);
  // put your main code here, to run repeatedly:

}
