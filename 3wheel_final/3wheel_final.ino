#include <Arduino.h>
// #include "CytronMotorDriver.h"
#include <IBusBM.h>
#define max_pwm 30

// BTS1
#define RPWM_M1 5
#define LPWM_M1 6

// BTS2
#define RPWM_M2 7
#define LPWM_M2 8

// BTS3
#define RPWM_M3 11
#define LPWM_M3 12


IBusBM ibus;

// Configure the motor driver.
void setMotorSpeeds(int speed1, int speed2, int speed3) {

  speed1 = speed1 % 180;
  speed2 = speed2 % 180;
  speed3 = speed3 % 180;

  //Serial.println(String(speed1) + " " + String(speed2) + " " + String(speed3));

  analogWrite(RPWM_M1, speed1 < 0 ? 0 : abs(speed1));
  analogWrite(LPWM_M1, speed1 < 0 ? abs(speed1) : 0);  // Handle motor direction
  analogWrite(RPWM_M2, speed2 < 0 ? 0 : abs(speed2));
  analogWrite(LPWM_M2, speed2 < 0 ? abs(speed2) : 0);  // Handle motor direction
  analogWrite(RPWM_M3, speed3 < 0 ? 0 : abs(speed3));
  analogWrite(LPWM_M3, speed3 < 0 ? abs(speed3) : 0);  // Handle motor direction
}


// Red the channel and return a boolean value
void convert(int x, int y, int z_rotation) {

  float wheelSeparation = 0.33;  // Hight and width meters
  float wheelRadius = 0.1035;    // radius in meters
  float wheelAngle = 120.0 * (PI / 180.0);
  y *= 0.6;
  float wheel1 = (-x * cos(wheelAngle) + y * sin(wheelAngle) - (wheelSeparation / 2.0) * z_rotation * 1) / wheelRadius;
  float wheel2 = (-x * cos(wheelAngle) - y * sin(wheelAngle) - (wheelSeparation / 2.0) * z_rotation * 1) / wheelRadius;
  float wheel3 = (-x - (wheelSeparation / 2.0) * z_rotation * 1) / wheelRadius;


  int front_left_ = map(wheel1, -100, 100, -max_pwm, max_pwm);
  int front_right_ = map(wheel2, 100, -100, -max_pwm, max_pwm);
  int back_back_ = map(wheel3, -100, 100, -max_pwm, max_pwm);

  //char output[100];
  // sprintf(output, "Wheel 1 -> %-4d Wheel 2 -> %-4d Wheel 3 -> %-4d", x, y, z_rotation * 2);
  //Serial.println(output);

  // Serial.println(String(front_left_) + " " + String(front_right_) + " " + String(back_back_));

  setMotorSpeeds(front_left_, front_right_, back_back_);
}
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100)
    return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// The setup routine runs once when you press reset.
void setup() {
  delay(2000);
  // MOTOR 1
  pinMode(RPWM_M1, OUTPUT);
  pinMode(LPWM_M1, OUTPUT);
  // MOTOR 2
  pinMode(RPWM_M2, OUTPUT);
  pinMode(LPWM_M2, OUTPUT);
  // MOTOR 3
  pinMode(RPWM_M3, OUTPUT);
  pinMode(LPWM_M3, OUTPUT);

  HardwareSerial &ibusRcSerial = Serial1;
  HardwareSerial &aSerial = Serial;
  aSerial.begin(115200);
  ibus.begin(ibusRcSerial);
}

// The loop routine runs over and over again forever.

void loop() {

  //drive
  int X_axis = readChannel(0, -100, 100, 0);  //ch1
  int Y_axis = readChannel(1, -100, 100, 0);  //ch2
  int z_axis = readChannel(3, -100, 100, 0) +5; //ch4

  //robo arm


  char output_1[100];
  //sprintf(output_1, "ch 1 -> %-4d ch 2 -> %-4d ch 3 -> %-4d ", Y_axis, X_axis, z_axis);
  // Serial.println(output_1);
   Serial.println(String(Y_axis)+" "+String(X_axis)+" "+String(z_axis));
  convert(X_axis, Y_axis, z_axis);
  delay(10);
}