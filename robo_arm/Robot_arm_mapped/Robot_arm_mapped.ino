#include<Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servoL;
Servo servoR;

int x1_key = A0;                                               
int y1_key = A1;   
int x2_key = A2;
int y2_key = A3;      

int initial_position = 90;

int x1_pos = initial_position;
int y1_pos = initial_position;
int x2_pos = initial_position;
int y2_pos = initial_position;

int x1_val;
int x2_val;
int y1_val;
int y2_val;

int servo1_pin = 2;
int servo2_pin = 3;  
int servo3_pin = 4;
int servoL_pin = 5;
int servoR_pin = 6;

int minDelta = 10;

int min_x1 = 10;
int max_x1 = 170;
int min_y1 = 10;
int max_y1 = 170;
int min_x2 = 10;
int max_x2 = 170;
int min_y2 = 60;
int max_y2 = 170;

void setup () {

  Serial.begin (9600);

  // for (int i = 2; i<=6; i++) {
  //   servo1.attach (i);
  // } 

  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servoL.attach(5);
  servoR.attach(6);

  servo1.write(initial_position);
  servo2.write(initial_position);
  servo3.write(initial_position);
  servoL.write(initial_position);
  servoR.write(initial_position);

  pinMode(x1_key, INPUT);
  pinMode(y1_key, INPUT);
  pinMode(x2_key, INPUT);
  pinMode(y2_key, INPUT);
}

void loop ( ) {
  x1_val = analogRead(x1_key);  
  y1_val = analogRead(y1_key);
  x2_val = analogRead(x2_key);
  y2_val = analogRead(y2_key);

  // position updation:

  //x1 

  if  (abs(x1_val - 512) > minDelta) {
          x1_pos += map ((x1_val - 512), -512, 511, 3, -3);
  }

  //y1

  if  (abs(y1_val - 512) > minDelta) {
          y1_pos += map ((y1_val - 512), -512, 511, -3, 3);
  }

  //x2

  if  (abs(x2_val - 512) > minDelta) {
          y2_pos += map ((x2_val - 512), -512, 511, -5, 5);
  }

  //y2

  if  (abs(y2_val - 512) > minDelta) {
          x2_pos += map ((y2_val - 512), -512, 511, 5, -5);
  }

  // Limiting values:

  if (x1_pos > max_x1) {x1_pos = max_x1;}
  if (y1_pos > max_y1) {y1_pos = max_y1;}
  if (x1_pos < min_x1) {x1_pos = min_x1;}
  if (y1_pos < min_y1) {y1_pos = min_y1;}

  if (x2_pos > max_x2) {x2_pos = max_x2;}
  if (y2_pos > max_y2) {y2_pos = max_y2;}
  if (x2_pos < min_x2) {x2_pos = min_x2;}
  if (y2_pos < min_y2) {y2_pos = min_y2;}
  

  // Printing position values

  Serial.print(x1_pos);
  Serial.print("\t");
  Serial.print(y1_pos);
  Serial.print("\t");
  Serial.print(x2_pos);
  Serial.print("\t");
  Serial.print(y2_pos);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(x1_val-512);
  Serial.print("\t");
  Serial.print(y1_val-512);
  Serial.print("\t");
  Serial.print(x2_val-512);
  Serial.print("\t");
  Serial.print(y2_val-512);
  Serial.println("");

  //Writing into servos:

  servo1.write(x1_pos);
  servo2.write(y1_pos);
  servo3.write(x2_pos);
  servoL.write(y2_pos);
  servoR.write(map(y2_pos, 0, 180, 180, 0));


  delay(50);
}