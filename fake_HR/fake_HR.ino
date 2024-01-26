#include <Arduino.h>
#include <Adafruit_Sensor.h>

const int analogPin = 18;  // Analog input connected to the AD8232 output
const int loPlusPin = 2;   // LO+ connected to D2
const int loMinusPin = 4;  // LO- connected to D4


unsigned long lastBeatTime;
int N;
float BPM;
int Signal;
bool pulse, beatDetected;
int threshold;
int ibi[10];
int ibiSum;

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(loPlusPin, INPUT);
  pinMode(loMinusPin, INPUT);
  Serial.begin(115200);
  Serial.println("AD8232 Heart Rate Sensor Example");

  lastBeatTime = 0;
  N = 10;
  BPM = 0;
  Signal = 0;
  pulse = false;
  beatDetected = false;
  threshold = 550;
  ibiSum = 0;
  for (int i = 0; i < N; i++) {
    ibi[i] = 600;
  }
}

void loop() {
  int rawValue = analogRead(analogPin);
  int loPlusValue = digitalRead(loPlusPin);
  int loMinusValue = digitalRead(loMinusPin);

  Signal = rawValue;

  if (loPlusValue == HIGH || loMinusValue == HIGH) {
    Signal = 0;
    Serial.println("Place the sensor on your chest.");
  } else {
    if (Signal > threshold) {
      if (beatDetected == false) {
        beatDetected = true;
        ibi[0] = millis() - lastBeatTime;
        lastBeatTime = millis();

        int runningTotal = 0;
        for (int i = 0; i < N - 1; i++) {
          ibi[i] = ibi[i + 1];
          runningTotal += ibi[i];
        }

        ibi[N - 1] = millis() - lastBeatTime;
        runningTotal += ibi[N - 1];
        runningTotal /= N;
        BPM = 60000 / runningTotal;
      }
    }

    if (Signal < threshold) {
      beatDetected = false;
    }
  }
  //real
  if (millis() - lastBeatTime >= 2000) {
    BPM = 0;
    ibiSum = 0;
    for (int i = 0; i < N; i++) {
      ibi[i] = 600;
    }
  }
  // Serial.print("BPM: ");
  // Serial.println(BPM);


  //fake
  int frt = 75;      // Starting heart rate value
  int change = random(-5, 6);  // Simulate small changes up or down
  frt += change;
  frt = constrain(frt, 60, 120);
  // Print the heart rate value
  if (loPlusValue == HIGH || loMinusValue == HIGH) {
    Serial.println("Place the sensor on your chest.");
    frt = 0;
  } else {
    Serial.print("Heart Rate: ");
    Serial.print(frt);
    Serial.println(" BPM");

    // Send data to the Serial Plotter
    Serial.println(frt);
  }

  delay(500);
}
