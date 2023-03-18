#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <ESP8266WiFi.h>

#define tot 5     //sets total number of people
#define totfac 1  //sets total number of faculty
//WIFI
const char* ssid = "DIPTAYAN-JASH 0982";
const char* password = "G662+28k";

//DISPLAY
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int flag;
int fac_flag;  //faculty flag
int pos;
int fac_pos;  //faculty pos

//RFID
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;
MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class
MFRC522::MIFARE_Key key;
String faculty_tag;


//SDCARD
File myfile;                //create a file named attendance
constexpr uint8_t cs = D8;  //NODE MCU

//ID CARD DETAILS
String facUID[totfac] = { "249224147101" };
char facname[totfac] = { 'm' };
String UID[tot] = { "20115312290", "105199145101", "2176091112", "89195136101" };
String name[tot] = { "Krrish", "Ayan", "Daniel", "Siddhima" };

char fac;
String old = "";

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
  String a = read_rfid();
  Serial.println(a);
  for (int i = 0; i < totfac; i++) {
    if (a == facUID[i]) {
      Serial.println(a);
      fac_flag = 1;
      fac_pos = i;
      break;
    } else
      fac_flag = 0;
  }
  if (fac_flag == 1) {
    switch (facname[fac_pos]) {
      case 'm':
        {
          //String student = read_rfid();
          for (int i = 0; i < tot; i++) {
            if (student == UID[i]) {
              pos = i;
              flag = 1;
              break;
            } else
              flag = 0;
          }
          if (flag == 1)
            Serial.println("student present");
          else Serial.println("invalid");
        }
        break;
      default:
        {
          Serial.println("faculty not found");
        }
        break;
    }
  }
  else
    Serial.println("INVALID FACULTY");
}

String read_rfid() {
  String tag = "";
  if (!rfid.PICC_IsNewCardPresent())
    return "";
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return tag;
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