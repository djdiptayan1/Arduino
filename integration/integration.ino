#include <Arduino.h>
#include <Servo.h>
#include "CytronMotorDriver.h"
#include <IBusBM.h>
#define max_pwm 60

Servo servo1;
Servo servo2;

IBusBM ibus;

// Configure the motor driver.



CytronMD motor1(PWM_DIR, 11, A12);  //side with fuses
CytronMD motor2(PWM_DIR, 9, A14);   // side with cytron and mega
CytronMD motor3(PWM_DIR, 12, A13);  // side with only cytron //slow motor

// Red the channel and return a boolean value
void convert(int x, int y, int z_rotation) {

  float wheelSeparation = 0.33;  // Hight and width meters
  float wheelRadius = 0.1035;    // radius in meters
  float wheelAngle = 120.0 * (PI / 180.0);
  y *= 0.6;
  float wheel1 = (-x * cos(wheelAngle) + y * sin(wheelAngle) - (wheelSeparation / 2.0) * z_rotation * 1) / wheelRadius;
  float wheel2 = (-x * cos(wheelAngle) - y * sin(wheelAngle) - (wheelSeparation / 2.0) * z_rotation * 1) / wheelRadius;
  float wheel3 = (-x - (wheelSeparation / 2.0) * z_rotation * 1) / wheelRadius;

  int front_left_ = map(wheel1, -100, 100, -max_pwm, max_pwm) * 0.5 * 0.5;
  int front_right_ = map(wheel2, -100, 100, -max_pwm, max_pwm) * 0.5 * 0.5;
  int back_back_ = map(wheel3, -100, 100, -max_pwm, max_pwm) * 0.5 * 0.5;

  //char output[100];
 // sprintf(output, "Wheel 1 -> %-4d Wheel 2 -> %-4d Wheel 3 -> %-4d", x, y, z_rotation * 2);
  //Serial.println(output);

   Serial.println(String(front_left_)+" "+String(front_right_)+" "+String(back_back_));

  motor1.setSpeed(front_left_);       // Motor 1 stops.
  motor2.setSpeed(front_right_);      // Motor 2 stops.
  motor3.setSpeed(back_back_);  // Motor 1 stops.
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
  HardwareSerial &ibusRcSerial = Serial1;
  HardwareSerial &aSerial = Serial;
  aSerial.begin(115200);
  ibus.begin(ibusRcSerial);
  servo1.attach(A1);
  servo2.attach(A2);
}

// The loop routine runs over and over again forever.

void loop() {

  int X_axis = readChannel(0, -100, 100, 0);     //ch1
  int Y_axis = readChannel(2, -100, 100, 0);     //ch2
  int z_axis = readChannel(3, -100, 100, 0);     //ch4
  int BaseJoint = readChannel(4, -100, 100, 0);  //but1

  //robo arm
  if (BaseJoint > 0) {

    servo1.write(0);
    delay(100);
    servo2.write(90);
    delay(100);

  } else {

    servo1.write(75);
    delay(100);
    servo2.write(17);
    delay(100);
  }

  char output_1[100];
  //sprintf(output_1, "ch 1 -> %-4d ch 2 -> %-4d ch 3 -> %-4d ", Y_axis, X_axis, z_axis);
  // Serial.println(output_1);

  // Serial.println(String(Y_axis)+" "+String(X_axis)+" "+String(z_axis));
  convert(X_axis, Y_axis, z_axis);
  delay(10);
}