#include <IBusBM.h>
IBusBM ibus;
#define IR1 1
#define IR2 2
#define IR3 3
#define IR4 4
#define IR5 5
//BTS
int R_PWM = 9;
int L_PWM = 10;
//relay
#define relay 7

//char inp = 's';
int max=10;

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
  digitalWrite(R_PWM, 0);
  digitalWrite(L_PWM, max);
}
void backward() {
  digitalWrite(R_PWM, max);
  digitalWrite(L_PWM, 0);
}
void stop() {
  digitalWrite(R_PWM, 0);
  digitalWrite(L_PWM, 0);
}
void setup() {
  Serial.begin(9600);
  //IR
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  //relay
  pinMode(relay, OUTPUT);
  //motor
  pinMode(R_PWM, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  //pinMode(in2, OUTPUT);
    ibus.begin(Serial);
}

void loop() {
  int value = readChannel(1, -100, 100, 0);
 //inp = Serial.read();
  digitalWrite(relay, LOW);
  int Switch = 2;
  flagtrig = 1;
  if (value >=20) {
    backward();
    Serial.println("backward");
  }
  else if (value <=-15) {
    forward();
    Serial.println("forward");
  }
  else{
    stop();
    Serial.println("stop");
  }
  // if (inp == 'r'){
  //   digitalWrite(relay, HIGH);
  //   delay(500);
  //   Serial.println("shoot");
  //   }
}