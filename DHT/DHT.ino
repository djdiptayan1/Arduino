#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define DHTPIN  13          // Digital pin 2
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN,  DHTTYPE);

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET 4      // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){
  Serial.begin(9600);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {  // Address   0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }
  pinMode(DHTPIN, INPUT);
}
void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
   display.clearDisplay();

  Serial.print("\tTemperature : ");
  Serial.print(t);
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.println("Temperature :");
  display.setTextSize(1);
  display.setCursor(80, 40);
  display.println(t);
  display.setTextSize(1);
  display.setCursor(115, 40);
  display.println("C");

  Serial.print("\tHumidity : ");
  Serial.println(h);
  display.setTextSize(1);
  display.setCursor(0, 54);
  display.println("Humidity    :");
  display.setTextSize(1);
  display.setCursor(80, 54);
  display.println(h);
  display.setTextSize(1);
  display.setCursor(115, 54);
  display.println("%");
  display.display();
  //delay(1000);
}