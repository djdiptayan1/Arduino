//Tech Trends Shameer

#define BLYNK_TEMPLATE_ID "TMPLoFo97whX"
#define BLYNK_TEMPLATE_NAME "Air Quality"
#define BLYNK_AUTH_TOKEN "2XMs0svi0q-tUNQO-GDT1aabnygjSFSh"

#define BLYNK_PRINT Serial
#include <WiFi.h>
//#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "iQOO Z5";    // type your wifi name
char pass[] = "123456789";  // type your wifi password

BlynkTimer timer;


#define DHTPIN 13  //Connect Out pin to D2 in NODE MCU
#define gas 34
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float value =0.00;
void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // or dht.readTemperature(true) for Fahrenheit
   value = analogRead(gas);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, value);
  Serial.print("Air Quality : ");
  Serial.print(value);
  Serial.print("\tTemperature : ");
  Serial.print(t);
  Serial.print("\tHumidity : ");
  Serial.println(h);
}
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(gas, INPUT);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}