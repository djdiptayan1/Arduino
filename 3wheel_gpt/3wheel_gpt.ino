/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 *
 * This example shows how to drive 3 motors using the PWM and DIR pins with
 * a 3-wheel drive system oriented at 120 degrees angle.
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>
#include "CytronMotorDriver.h"

//Initializing NRF and address
RF24 radio(48, 49);               // CE, CSN
const byte address[6] = "SIDMA";  //Address for communication between NRF
int8_t command[20];

#define max_pwm 60

// Motor driver configuration
CytronMD motor1(PWM_DIR, 10, A15);  // Motor 1: PWM = Pin 10, DIR = Pin A15.
CytronMD motor2(PWM_DIR, 9, A14);   // Motor 2: PWM = Pin 9, DIR = Pin A14.
CytronMD motor3(PWM_DIR, 12, A13);  // Motor 3: PWM = Pin 12, DIR = Pin A13.


void convert(int xVel, int yVel, int zAngular) {
  // Wheel geometry parameters
  double wheelRadius = 0.1035;             // Radius in meters
  double wheelSeparation = 0.33;  // Width and height in meters
  double wheelAngle = 120.0 * (PI / 180.0);


  // Calculate wheel speeds for a 3-wheel drive system oriented at 120 degrees
  double wheelSpeeds[3];
  wheelSpeeds[0] = (-xVel - (wheelSeparation / 2.0) * zAngular) / wheelRadius;
  wheelSpeeds[1] = (-xVel * cos(wheelAngle) + yVel * sin(wheelAngle) - (wheelSeparation / 2.0) * zAngular) / wheelRadius;
  wheelSpeeds[2] = (-xVel * cos(wheelAngle) - yVel * sin(wheelAngle) - (wheelSeparation / 2.0) * zAngular) / wheelRadius;

  // Convert wheel speeds to PWM values
  int pwmValues[3];
  for (int i = 0; i < 3; i++) {
    pwmValues[i] = map(wheelSpeeds[i], -max_pwm, max_pwm, -1000, 1000);
  }

  // Set motor speeds
  motor1.setSpeed(pwmValues[0]);
  motor2.setSpeed(pwmValues[1]);
  motor3.setSpeed(pwmValues[2]);
}

// The setup routine runs once when you press reset.
void setup() {
  Serial.begin(9600);
  radio.begin();
  //Initialising NRF
  if (radio.isChipConnected()) {
    Serial.print("NRF SPI is Connected");
  }
  radio.setChannel(100);
  radio.setPayloadSize(20);
  radio.setDataRate(RF24_2MBPS);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

// The loop routine runs over and over again forever.
void loop() {
  if (radio.available()) {
    radio.read(&command, sizeof(command));
    command[1] = command[1] - 128;
    command[2] = (int)command[2] - 128;
    command[3] = (int)command[3] - 128;
               for(int i = 0; i < 20; i++)
               {
                   Serial.print(command[i]);
                   Serial.print(" ");
               }
               Serial.println();
  }

  // Convert channel values to motor commands
  convert(command[1], command[2], command[3]);

  delay(10);
}
