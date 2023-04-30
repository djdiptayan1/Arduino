#define JOYLX A2
#define JOYLY A3
#define JOYRX A1
#define JOYRY A0

#define RA 5
#define RB 4
#define RC 3
#define RD 2

#define LA 7
#define LB 6
#define LC A4
#define LD A5

#define TOG 8

uint16_t IN[13];

void setup() {
  Serial.begin(9600);
  memset(&IN, 0, sizeof(IN));
  
  pinMode(JOYLX, INPUT);
  pinMode(JOYLY, INPUT);
  pinMode(JOYRX, INPUT);
  pinMode(JOYRY, INPUT);

  pinMode(RA, INPUT);   //need to declare each button as an
  pinMode(RB, INPUT);   //INPUT
  pinMode(RC, INPUT);
  pinMode(RD, INPUT);

  pinMode(LA, INPUT);   //need to declare each button as an
  pinMode(LB, INPUT);   //INPUT
  pinMode(LC, INPUT);
  pinMode(LD, INPUT);

  pinMode(TOG, INPUT);
}


void loop() {
  IN[0] = digitalRead(RA);
  IN[1] = digitalRead(RB);
  IN[2] = digitalRead(RC);
  IN[3] = digitalRead(RD);

  IN[4] = digitalRead(LA);
  IN[5] = digitalRead(LB);
  IN[6] = digitalRead(LC);
  IN[7] = digitalRead(LD);

  IN[8] = analogRead(JOYLX);
  IN[9] = analogRead(JOYLY);
  IN[10] = analogRead(JOYRX);
  IN[11] = analogRead(JOYRY);

  IN[12] = digitalRead(TOG);

  for(int i=0;i<13;i++){
    Serial.print(" ");
    Serial.print(IN[i]);
  }
  Serial.println();
  delay(10);
}