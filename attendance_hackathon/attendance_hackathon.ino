#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define tot 5  //sets total number of people
//WIFI
const char* ssid = "DIPTAYAN-JASH 0982";
const char* password = "G662+28k";

//DISPLAY
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int flag;
int pos = 0;

//RFID
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;
MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class
MFRC522::MIFARE_Key key;
String tag;

//SDCARD
File myfile;                   //create a file named attendance
constexpr uint8_t cs = D8;     //NODE MCU
constexpr uint8_t relay = D0;  //relay

//ID CARD DETAILS
String UID[tot] = { "20115312290", "249224147101", "105199145101", "2176091112", "89195136101" };
String name[tot] = { "Krrish", "Diptayan", "Ayan", "Daniel", "Siddhima" };

//GOOGLE SHEET
String server = "http://maker.ifttt.com";
String eventName = "data";
String IFTTT_Key = "baQbPWpUvivRmuUXHnRzxd";
String IFTTTUrl = "https://maker.ifttt.com/trigger/data/with/key/baQbPWpUvivRmuUXHnRzxd";
String value1;
String value2;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  //SD CARD
  //sdinitialize();
  //wifi
  //connectwifi();
}

void loop() {
  String data = "";
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("scan");
  lcd.setCursor(1, 1);
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    //checking
    for (int i = 0; i < tot; i++) {
      if (tag == UID[i]) {
        flag = 1;
        pos = i;
        break;
      } else {
        flag = 0;
      }
    }

    if (flag == 1) {
      value1 = name[pos];  //for google sheets
      value2 = UID[pos];   // for google sheets
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Welcome");
      lcd.setCursor(1, 1);
      Serial.println(name[pos]);
      lcd.println(name[pos]);
      delay(2000);
      myfile = SD.open("attendance.csv", FILE_WRITE);
      data = name[pos] + "," + UID[pos];
      myfile.println(data);
      Serial.println("WROTE IN FILE SUCCESSFUL");
      myfile.close();
      sendDataToSheet();
    } else {
      value1 = "UNKNOWN";  //for google sheets
      value2 = tag;        // for google sheets
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Who Tf is You ?");
      lcd.setCursor(1, 1);
      lcd.print(tag);
      Serial.println(tag);
      delay(2000);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}
void connectwifi() {
  Serial.print("Wifi connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP());
  client.setInsecure();
}
void sdinitialize() {
  Serial.println("Initializing SD card");
  if (!SD.begin(cs)) {
    Serial.println("initialization failed");
    while (1)
      ;
  }
  Serial.println("initialization DONE");
  if (SD.exists("attendance.csv"))
    Serial.println("FILE EXISTS");
  else
    Serial.println("FILE DOESN'T EXISTS");
}
void sendDataToSheet(void) {
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + value1 + "&value2=" + value2 + "&value3=" + value3;
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url);  //HTTP
  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}