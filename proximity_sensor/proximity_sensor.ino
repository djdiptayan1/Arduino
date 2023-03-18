const int pin=2;

void setup()
{
  Serial.begin(9600);
  pinMode(pin,INPUT);
}

void loop() {
  int value=digitalRead(pin);
  if(value==HIGH){
    Serial.println("OBJECT DETECTED");
    delay (300);
  }
  else{
    Serial.println("NO OBJECT");
    delay (400);
  }
  }
