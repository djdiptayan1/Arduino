#define lpwm_pin 7
#define rpwm_pin 8
int maxpwm = 255;

String com;

void setup() {
  Serial.begin(57600);
  Serial.println("BTS DRIVER TESTER");
  pinMode(lpwm_pin, OUTPUT);
  pinMode(rpwm_pin, OUTPUT);
}

void loop() {
  //com=Serial.readString();
  while (Serial.available() == 0) {
    if(Serial.read()== 'f'){
    digitalWrite(lpwm_pin, HIGH);
    digitalWrite(rpwm_pin, LOW);
    Serial.println("FORWARD");
    }
    //delay(5000);
    if(Serial.read()== 'b'){
    digitalWrite(lpwm_pin, LOW);
    digitalWrite(rpwm_pin, HIGH);
    Serial.println("BACKWARD");
    }
    //delay(5000);
  }
}
