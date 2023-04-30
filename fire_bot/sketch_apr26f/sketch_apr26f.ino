#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <MPU6050.h>
#include <Wire.h>
Servo myservo;

int Xaxis, Zaxis, Yaxis;
MPU6050 mpu;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

//MOTOR DRIVER
#define en1 2
#define en2 7
#define inl1 3
#define inl2 4
#define inr1 5
#define inr2 6

//IR
#define ir1 52
#define ir2 50
#define ir3 48

//SERVO PIN
#define servopin 8

//PUMP
#define pump 11

//buzzer
#define push 46
#define buzz 9

//EARTHQUAKE
int earthquake = 0;

//MQ2
#define gas A0
#define thresh 100
boolean fire = false;
int sensorValue = 0;

void forward() {
  digitalWrite(inl1, HIGH);
  digitalWrite(inl2, LOW);
  digitalWrite(inr1, HIGH);
  digitalWrite(inr2, LOW);
}
void back() {
  digitalWrite(inl1, LOW);
  digitalWrite(inl2, HIGH);
  digitalWrite(inr1, LOW);
  digitalWrite(inr2, HIGH);
}
void right() {
  digitalWrite(inl1, HIGH);
  digitalWrite(inl2, LOW);
  digitalWrite(inr1, LOW);
  digitalWrite(inr2, HIGH);
}
void left() {
  digitalWrite(inl1, LOW);
  digitalWrite(inl2, HIGH);
  digitalWrite(inr1, HIGH);
  digitalWrite(inr2, LOW);
}
void stop() {
  digitalWrite(inl1, LOW);
  digitalWrite(inl2, LOW);
  digitalWrite(inr1, LOW);
  digitalWrite(inr2, LOW);
}
void put_off_fire() {
  delay(500);
  stop();
  digitalWrite(pump, HIGH);
  delay(500);
  for (int pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (int pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  digitalWrite(pump, LOW);
  myservo.write(90);
  fire = false;
  earthquake = 0;
}

void setup() {
  Serial.begin(115200);
  //IR SENSORS
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  //MOTOR DRIVER
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(inl1, OUTPUT);
  pinMode(inl2, OUTPUT);
  pinMode(inr1, OUTPUT);
  pinMode(inr2, OUTPUT);
  //PWM
  digitalWrite(en1, 127);
  digitalWrite(en2, 127);
  //SERVO
  myservo.attach(servopin);
  myservo.write(90);
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  checkSettings();

  lcd.init();
  lcd.clear();
  lcd.backlight();  // Make sure backlight is on
}
void loop() {

  //EARTHQUAKE
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  Xaxis = rawAccel.XAxis;
  Yaxis = rawAccel.YAxis;
  Zaxis = rawAccel.ZAxis;
  if (rawAccel.XAxis < 17000) {
    Xaxis = 0;
  }
  if (rawAccel.YAxis < 700) {
    Yaxis = 0;
  }
  if (rawAccel.XAxis > 17000 || rawAccel.YAxis > 700) {
    Serial.println("-----------EARTHQUAKE------------");
    earthquake = 1;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("EARTHQUAKE");
    delay(1000);
  }

  sensorValue = (analogRead(gas)) / 3;  // read analog input pin 0
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  if (sensorValue > thresh) {
    Serial.print(" | Smoke detected!");
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("SMOKE");
    delay(1000);
    lcd.clear();
  }
  Serial.println();

  //BUZZER
  if (digitalRead(push) == 0) {
    digitalWrite(buzz, HIGH);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("PERSON DETECTED");
    delay(1000);
    lcd.clear();
  }
    if (digitalRead(ir1) == 1 && digitalRead(ir2) == 1 && digitalRead(ir3) == 1) {
      stop();
    }
    if (digitalRead(ir1) == 0) {
      left();
    }
    if (digitalRead(ir2) == 0) {
      fire = true;
      forward();
    }
    if (digitalRead(ir3) == 0) {
      right();
    }
    delay(300);
    if (fire == true) {
      put_off_fire();
    }
}

void checkSettings() {
  Serial.println();

  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:          ");
  switch (mpu.getClockSource()) {
    case MPU6050_CLOCK_KEEP_RESET: Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO: Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO: Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO: Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ: Serial.println("Internal 8MHz oscillator"); break;
  }

  Serial.print(" * Accelerometer:         ");
  switch (mpu.getRange()) {
    case MPU6050_RANGE_16G: Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G: Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G: Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G: Serial.println("+/- 2 g"); break;
  }

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());

  Serial.println();
}