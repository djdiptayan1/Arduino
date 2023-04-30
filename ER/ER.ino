#include <IBusBM.h>

// Create iBus Object
IBusBM ibus;
//hercules
int pwm = 127;
// #define en 1
#define lpwm 2
#define rpwm 3
#define ren 4
#define len 5
//relay
#define relay 7

int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
int flag, flagtrig;

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
void forward() {
  digitalWrite(lpwm, pwm);
  digitalWrite(rpwm, 0);
}
void backward() {
  digitalWrite(lpwm, 0);
  digitalWrite(rpwm, pwm);
}
void stop() {
  digitalWrite(lpwm, 0);
  digitalWrite(rpwm, 0);
}
void setup() {
  Serial.begin(9600);
  ibus.begin(Serial1);
  //relay
  pinMode(relay, OUTPUT);
  //motor
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(ren, HIGH);
  digitalWrite(len, HIGH);
}

void loop() {
  int Shoot = readSwitch(4, false);
  int ch2 = readChannel(1, -100, 100, 0);

  //pwm=map(y_val, -100,100,255,255);
  Serial.print(pwm);
  if (ch2 > 10) {
    forward();
    Serial.println("FORWARD");
  } else if (ch2 < -10) {
    backward();
    Serial.println("BACKWARD");
  } else {
    stop();
    Serial.println("STOP");
  }
  if (Shoot == 1) {
    digitalWrite(relay, LOW);
    Serial.println("SHOOT")
  } else {
    digitalWrite(relay, HIGH);
  }
}