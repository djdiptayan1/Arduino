#include <IBusBM.h>
IBusBM ibus;
#define IR1 8
#define IR2 9
#define IR3 10
#define IR4 11
#define IR5 12
//hercules
#define pwm 127
#define en 1
#define in1 2
#define in2 3
//relay
#define relay 7

int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
int flag, flagtrig;

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
  pinMode(en, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  // int Switch = ibus.readChannel(5);
  // int Switch=map(switch, 0, 1000, 0,2)
  int Switch = 2;
  /*
    read whether the ring is pushed or not
    flagtrig=1;
  */
  flagtrig = 1;
  //READING IR VALUE
  int ir1_value = digitalRead(IR1);
  int ir2_value = digitalRead(IR2);
  int ir3_value = digitalRead(IR3);
  int ir4_value = digitalRead(IR4);
  int ir5_value = digitalRead(IR5);

  if (ir1_value == 0) {
    flag1 = 1;
  }
  if (ir2_value == 0) {
    flag2 = 1;
  }
  if (ir3_value == 0) {
    flag3 = 1;
  }
  if (ir4_value == 0) {
    flag4 = 1;
  }
  if (ir5_value == 0) {
    flag5 = 1;
  }

  if (flagtrig == 1 && flag == 0) {
    //relay HIGH;
    digitalWrite(relay, HIGH);
    Serial.println("MOTOR FORWARD");
    forward();
  }
  switch (Switch) {
    case 2:
      if (flag == 0 && flag2 == 1) {
        flag = 1;
        //shoot;
        Serial.println("IR 2 TRIG");
        digitalWrite(relay, LOW);
      }
      break;
    case 3:
      if (flag == 0 && flag2 == 1) {
        flag = 1;
        //shoot;
        Serial.println("IR 3 TRIG");
        digitalWrite(relay, LOW);
      }
      break;
  }

  if (flag1 == 0 && flag == 1) {
    backward();
    Serial.println("shoot and move back");
  }
  if (flag1 == 1 && flag == 1) {
    stop();
    Serial.println("STOPPED");
    flag=0;
  }
}