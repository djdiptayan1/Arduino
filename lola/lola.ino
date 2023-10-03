#include "CytronMotorDriver.h"
#include <IBusBM.h>

#define speed 90

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

void forward() {
  motor1.setSpeed(90);  // Motor 1 stops.
  motor2.setSpeed(90);  // Motor 2 stops.
  motor3.setSpeed(0);   // Motor 1 stops.
}
void back() {
  motor1.setSpeed(-90);  // Motor 1 stops.
  motor2.setSpeed(-90);  // Motor 2 stops.
  motor3.setSpeed(0);    // Motor 1 stops.
}
void stop() {
  motor1.setSpeed(0);  // Motor 1 stops.
  motor2.setSpeed(0);  // Motor 2 stops.
  motor3.setSpeed(0);  // Motor 1 stops.
}
void clock() {
  motor1.setSpeed(45);  // Motor 1 stops.
  motor2.setSpeed(45);  // Motor 2 stops.
  motor3.setSpeed(45);  // Motor 1 stops.
}
void anti() {
  motor1.setSpeed(-45);  // Motor 1 stops.
  motor2.setSpeed(-45);  // Motor 2 stops.
  motor3.setSpeed(-45);  // Motor 1 stops.
}
void setup() {
  // put your setup code here, to run once:
  pinMode(m1p, OUTPUT);
  pinMode(m2p, OUTPUT);
  pinMode(m3p, OUTPUT);
  HardwareSerial &ibusRcSerial = Serial1;
  HardwareSerial &aSerial = Serial;
  aSerial.begin(115200);
  ibus.begin(ibusRcSerial);
}

void loop() {
  // put your main code here, to run repeatedly:
  int X_axis = readChannel(0, -100, 100, 0);  //ch1
  int Y_axis = readChannel(1, -100, 100, 0);  //ch2
  int z_axis = readChannel(3, -100, 100, 0);  //ch4

  if (Y_axis > 20) {
    forward();
    Serial.println("FORWARD");
  }
  if (Y_axis < 20) {
    back();
    Serial.println("back");
  }
  if (z_axis > 20) {
    clock();
    Serial.println("clock");
  }
  if (z_axis < 20) {
    anti();
    Serial.println("anti");
  } else {
    stop();
    Serial.println("stop");
  }
  delay(10);
}
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100)
    return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
