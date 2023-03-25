#include <SPI.h>
#include <Wire.h>
#include  <DHT.h>
#define DHTPIN  13          // Digital pin 2
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN,  DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
  pinMode(DHTPIN, INPUT);
}
void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("TEMPERATURE : ");
  Serial.print(t);
  Serial.print("\tHUMIDITY : ");
  Serial.println(h);
  //delay(1000);
}