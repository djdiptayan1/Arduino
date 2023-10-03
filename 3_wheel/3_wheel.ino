/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 *
 *
 * This example shows how to drive 2 motors using the PWM and DIR pins with
 * 2-channel motor driver.
 *
 *
 *
 *
 * Arduino D3  - Motor Driver PWM 1 Input  12
 * Arduino D4  - Motor Driver DIR 1 Input  9
 *
 * Arduino D9  - Motor Driver PWM 2 Input  11
 * Arduino D10 - Motor Driver DIR 2 Input  10
 * Arduino GND - Motor Driver GND
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

#include <Arduino.h>
#include "CytronMotorDriver.h"
#include <IBusBM.h>
#define max_pwm 90
#define mapval 1500

#define m1d A15
#define m1p 10
#define m2d A13
#define m2p 9
#define m3d A13
#define m3p 12

IBusBM ibus;

// Configure the motor driver.
CytronMD motor1(PWM_DIR, m1d, m1p);  // Motor 1: PWM = Pin 10, DIR = Pin A15.
CytronMD motor2(PWM_DIR, m2d, m2p);  // Motor 2: PWM = Pin 9, DIR = Pin A14.
CytronMD motor3(PWM_DIR, m3d, m3p);  // Motor 3: PWM = Pin 12, DIR = Pin A13.

// Red the channel and return a boolean value
void convert(int x, int y, int z_rotation) {

  float wheelSeparation = 0.33;  // Hight and width meters
  float wheelRadius = 0.1035;    // radius in meters
  float wheelAngle = 120.0 * (PI / 180.0);

  float wheel1 = (-x * cos(wheelAngle) + y * sin(wheelAngle) - (wheelSeparation / 2.0) * z_rotation) / wheelRadius;
  float wheel2 = (-x * cos(wheelAngle) - y * sin(wheelAngle) - (wheelSeparation / 2.0) * z_rotation) / wheelRadius;
  float wheel3 = (-x - (wheelSeparation / 2.0) * z_rotation) / wheelRadius;

  // char output[100];
  // sprintf(output, "Wheel 1 -> %-4d Wheel 2 -> %-4d Wheel 3 -> %-4d", wheel1, wheel2, wheel3);
  // Serial.println(output);

  int front_left_ = map(wheel1, -mapval, mapval, -max_pwm, max_pwm);
  int front_right_ = map(wheel2, -mapval, mapval, -max_pwm, max_pwm);
  int back_back_ = map(wheel3, -mapval, mapval, -max_pwm, max_pwm);

  char output[100];
  sprintf(output, "Wheel 1 -> %-4d Wheel 2 -> %-4d Wheel 3 -> %-4d", front_left_, front_right_, back_back_);
  Serial.println(output);

  // Serial.println(String(front_left)+" "+String(front_right)+" "+String(back_left)+" "+String(back_right));

  motor1.setSpeed(front_left_);   // Motor 1 stops.
  motor2.setSpeed(front_right_);  // Motor 2 stops.
  motor3.setSpeed(back_back_);    // Motor 1 stops.
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
}

// The loop routine runs over and over again forever.

void loop() {
  int X_axis = readChannel(0, -100, 100, 0);  //ch1
  int Y_axis = readChannel(1, -100, 100, 0);  //ch2
  int z_axis = readChannel(3, -100, 100, 0);  //ch4

  Y_axis -= 12;
  X_axis -= 12;
  z_axis += 12;
  if (Y_axis < 20 && Y_axis > -20) {
    Y_axis = 0;
  }

  char output_1[100];
  //sprintf(output_1, "ch 1 -> %-4d ch 2 -> %-4d ch 3 -> %-4d ", Y_axis, X_axis, z_axis);
  // Serial.println(output_1);

  // Serial.println(String(Y_axis)+" "+String(X_axis)+" "+String(z_axis));
  convert(X_axis, Y_axis, z_axis);
  delay(10);
}