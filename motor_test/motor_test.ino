#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Number of steps per output rotation
const int stepsPerRevolution = 200;
// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

#define inp1 2
#define inp2 3
#define inp3 4
#define inp4 5
#define inp5 6

#define touch 7
#define emergency 12

//BTS
#define RPWM 5
#define LPWM 6
#define REN 8
#define LEN 9

//STEPPER
#define step_clock A0
#define step_anti A1


void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();  // Make sure backlight is on

  Serial.begin(9600);
  //BTS
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(REN, OUTPUT);
  digitalWrite(REN, HIGH);
  digitalWrite(LEN, HIGH);

  // set the speed at 60 rpm:
  myStepper.setSpeed(60);

  //BUTTONS
  pinMode(inp1, INPUT);
  pinMode(inp2, INPUT);
  pinMode(inp3, INPUT);
  pinMode(inp4, INPUT);
  pinMode(inp5, INPUT);

  pinMode(touch, INPUT);
  pinMode(emergency, INPUT);
}

void loop() {

  //STEPPER MOTOR
  if (digitalRead(step_clock) == HIGH)
    myStepper.step(stepsPerRevolution);
  if (digitalRead(step_anti) == HIGH)
    myStepper.step(stepsPerRevolution);

  //TOUCH SENSOR
  if (digitalRead(touch) == HIGH || digitalRead(emergency) == HIGH) {
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("MOTOR OFF");
  }

  if (digitalRead(inp1) == HIGH) {
    Serial.println("25%");
    digitalWrite(LPWM, 51);
    digitalWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("25% POWER");
  }
  if (digitalRead(inp2) == HIGH) {
    Serial.println("40%");
    digitalWrite(LPWM, 102);
    digitalWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("40% POWER");
  }
  if (digitalRead(inp3) == HIGH) {
    Serial.println("60%");
    digitalWrite(LPWM, 153);
    digitalWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("60% POWER");
  }
  if (digitalRead(inp4) == HIGH) {
    Serial.println("80%");
    digitalWrite(LPWM, 204);
    digitalWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("80% POWER");
  }
  if (digitalRead(inp5) == HIGH) {
    Serial.println("100%");
    digitalWrite(LPWM, 255);
    digitalWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("100% POWER");
  }
}