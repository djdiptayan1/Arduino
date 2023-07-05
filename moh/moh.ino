#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Number of steps per output rotation
const int steps_per_rev = 200;  //Set to 200 for NIMA 17

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

//STEPPER
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define step_clock A0
#define step_anti A1
Stepper motor(steps_per_rev, IN1, IN2, IN3, IN4);


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
  if (digitalRead(step_clock) == 1) {
    Serial.println("CLOCKWISE STEPPER MOVEMENT");
    motor.step(steps_per_rev);
  }
  if (digitalRead(step_anti) == 1) {
    motor.step(-steps_per_rev);
    Serial.println("CLOCKWISE STEPPER MOVEMENT");
  }

  //TOUCH SENSOR
  if (digitalRead(touch) == 1 || digitalRead(emergency) == 1) {
    Serial.println("STOP");
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("MOTOR OFF");
  }

  if (digitalRead(inp1) == 1) {
    Serial.println("25%");
    analogWrite(LPWM, 51);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("25% POWER");
    delay(1000);  //TRY WITH DELAY ONCE, IF THERE IS A PROBLEM REMOVE DELAY
    lcd.clear();  //
  } else if (digitalRead(inp2) == 1) {
    Serial.println("40%");
    analogWrite(LPWM, 102);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("40% POWER");
    delay(1000);  //TRY WITH DELAY ONCE, IF THERE IS A PROBLEM REMOVE DELAY
    lcd.clear();  //
  } else if (digitalRead(inp3) == 1) {
    Serial.println("60%");
    analogWrite(LPWM, 153);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("60% POWER");
    delay(1000);  //TRY WITH DELAY ONCE, IF THERE IS A PROBLEM REMOVE DELAY
    lcd.clear();  //
  } else if (digitalRead(inp4) == 1) {
    Serial.println("80%");
    analogWrite(LPWM, 204);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("80% POWER");
    delay(1000);  //TRY WITH DELAY ONCE, IF THERE IS A PROBLEM REMOVE DELAY
    lcd.clear();  //
  } else if (digitalRead(inp5) == 1) {
    Serial.println("100%");
    analogWrite(LPWM, 255);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("100% POWER");
    delay(1000);  //TRY WITH DELAY ONCE, IF THERE IS A PROBLEM REMOVE DELAY
    lcd.clear();  //
  } else {
    Serial.println("OFF");
    analogWrite(LPWM, 0);
    analogWrite(RPWM, 0);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("OFF");
    delay(1000);  //TRY WITH DELAY ONCE, IF THERE IS A PROBLEM REMOVE DELAY
    lcd.clear();  //
  }
}