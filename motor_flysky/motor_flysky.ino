#include <IBusBM.h>
//hercules
#define pwm 127
#define en 1
#define in1 2
#define in2 3
//relay
#define relay 7
int motor;
IBusBM ibus;
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}
void forward() {
  digitalWrite(en, pwm);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void backward() {
  digitalWrite(en, pwm);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void setup() {
  Serial.begin(115200);
  ibus.begin(Serial1);
  //relay
  pinMode(relay, OUTPUT);
  //motor
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  int value = readChannel(2, -100, 100, 0);
  int sw=readSwitch(4, false);
  Serial.print("Ch 2\t");
  Serial.print(value);
  Serial.print("Ch6: "+sw);
  Serial.println();
  if (value > 0) {
    forward();
    Serial.println("FORWARD");
  } else if (value > -10 && value < 10) {
    stop();
    Serial.println("STOP");
  } else {
    backward();
    Serial.println("BACKWARD");
  }
  if(sw==1){
    digitalWrite(relay, HIGH);
    Serial.println("MAGNET ON");
  }
  else
  Serial.println("OFF");
  delay(10);
}