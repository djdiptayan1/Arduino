// ultrasonic left PINS
#define trigL A0  //TRIG PIN
#define echoL A1  //ECHO PIN
double durationL;
double distanceL;
// ultrasonic right PINS
#define trigR A2  //TRIG PIN
#define echoR A3  //ECHO PIN
double durationR;
double distanceR;

//BUZZER PINS
#define buzzL 5
#define buzzR 6

void setup() {
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);

  pinMode(buzzL, OUTPUT);
  pinMode(buzzR, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  //ULTRASONIC ON CODE
  digitalWrite(trigL, LOW);
  digitalWrite(trigR, LOW);
  delayMicroseconds(2);
  digitalWrite(trigL, HIGH);
  digitalWrite(trigR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigL, LOW);
  digitalWrite(trigR, LOW);

  durationL = pulseIn(echoL, HIGH);
  durationR = pulseIn(echoR, HIGH);

  //FINDING DISTANCE
  distanceL = (durationL * 0.034) / 2;
  distanceR = (durationR * 0.034) / 2;
  Serial.print("distance Left ");
  Serial.print(distanceL);
  Serial.print("\tdistance Right ");
  Serial.print(distanceR);
  Serial.println();
  delay(100);

  //FEEDBACK
  if (distanceL < 50) //LESS THAN 50 CM
  {
    digitalWrite(buzzL, HIGH);  //SETTING THE LEFT BUZZER ON
  }
  if (distanceR < 50) //LESS THAN 50 CM
  {
    digitalWrite(buzzR, HIGH);  //SETTING THE RIGHT BUZZER ON
  }
}