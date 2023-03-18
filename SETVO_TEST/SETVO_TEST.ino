#include <Servo.h>

//SERVO DECLARATION
Servo base; //base servo

//ANALOG INPUTS PINS DECLARATION
int basex=A0;

//STORES THE ANALOG INPUT VALUE
int valbase;

void setup() {

  //ATTACH THE SERVOS(DIGITAL)
  base.attach(2);
  
  Serial.begin(9600);
}

void loop() {

  //...............base...............
  valbase = analogRead(basex); //READ THE ANALOG INPUT AND STORES
  valbase = map(valbase, 0, 1023, 0, 145);
  base.write(valbase);  //
  Serial.println(valbase);
  delay(15); 
  
}
