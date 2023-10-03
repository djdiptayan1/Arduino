#include <Servo.h>
#include <IBusBM.h>

IBusBM ibus;

Servo servo1;
Servo servo2;

int initial_position = 60;

int x1_pos = initial_position;
int y1_pos = initial_position;

int x1_val;
int x2_val;

int minDelta = 10;

int min_x1 = 0;
int max_x1 = 75;
int min_y1 = 40;
int max_y1 = 120;

void setup() {

  Serial.begin(115200);

  // for (int i = 2; i<=6; i++) {
  //   servo1.attach (i);
  // }

  servo1.attach(A1);
  servo2.attach(A2);

  servo1.write(initial_position);
  servo2.write(initial_position);
  ibus.begin(Serial1);
}

void loop() {
  int x1_val = readChannel(3, 0, 1026, 512);
  int y1_val = readChannel(1, 0, 1026, 512);
  // position updation:

  //x1

  if (abs(x1_val - 512) > minDelta) {
    x1_pos += map((x1_val - 512), -512, 511, 3, -3);
  }

  //y1

  if (abs(y1_val - 512) > minDelta) {
    y1_pos += map((y1_val - 512), -512, 511, -3, 3);
  }

  // Limiting values:

  if (x1_pos > max_x1) { x1_pos = max_x1; }
  if (y1_pos > max_y1) { y1_pos = max_y1; }
  
  if (x1_pos < min_x1) { x1_pos = min_x1; }
  if (y1_pos < min_y1) { y1_pos = min_y1; }



  // Printing position values

  Serial.print(x1_pos);
  Serial.print("\t");
  Serial.print(y1_pos);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(x1_val - 512);
  Serial.print("\t");
  Serial.print(y1_val - 512);
  Serial.println("");

  //Writing into servos:

  servo1.write(x1_pos);
  servo2.write(y1_pos);

  delay(50);
}

int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}