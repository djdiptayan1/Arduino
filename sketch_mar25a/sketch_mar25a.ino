#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define DHTPIN 13  //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define SDA 21
#define SCL 22
void setup() {
  Wire.begin(SDA, SCL);
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {  // Address   0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(50, 0);
  display.println("Air");
  display.setTextSize(1);
  display.setCursor(23, 20);
  display.println("Qulaity monitor");
  display.display();

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(20, 20);
  display.println("BY Diptayan");
  display.display();
  display.clearDisplay();
}

void loop() {
  char in = Serial.read();
  float f = 3.11;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float value = 69.00;
  String quality = "Very bad!";
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 3);
  display.println("Air Quality :");
  display.setTextSize(1);
  display.setCursor(80, 3);
  display.println(value);
  display.setTextSize(2);
  display.setCursor(16, 18);
  display.println(quality);

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
  if (in == '3') {
    Serial.println("Three");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.println("Humidity :");
    display.setTextSize(1);
    display.setCursor(80, 40);
    display.println(value);
    display.display();
  }
  if (in == '4') {
    Serial.println("Four");
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 5);
    display.println("Air Quality :");
    display.setTextSize(1);
    display.setCursor(80, 30);
    display.println(value);
    display.display();
  }
}
