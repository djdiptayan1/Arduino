#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>

#define tot 5     //sets total number of people
#define factot 1  //sets the total number of faculty
//relay
constexpr uint8_t RELAY_PIN = D0;

//DISPLAY
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int flag;
int fac_flag;
int pos = 0;

//RFID
constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;
MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class
MFRC522::MIFARE_Key key;
String tag;
String faculty_tag;

//SDCARD
File myfile;                //create a file named attendance
constexpr uint8_t cs = D8;  //NODE MCU

//ID CARD DETAILS
String faculty[factot] = { "249224147101" };
String UID[tot] = { "20115312290", "105199145101", "2176091112", "89195136101" };
String name[tot] = { "Krrish", "Ayan", "Daniel", "Siddhima" };

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
  //RELAY
  pinMode(RELAY_PIN, OUTPUT);
  //SD CARD
  //sdinitialize();
  //WIFI
}

void loop() {
  digitalWrite(RELAY_PIN, HIGH);
  String data = "";
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      faculty_tag += rfid.uid.uidByte[i];
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    //faculty checking
    for (int i = 0; i < factot; i++) {
      if (faculty_tag == faculty[i]) {
        fac_flag = 1;
        break;
      } else
        fac_flag = 0;
    }

    if (fac_flag == 1) {
      //checking
      if (!rfid.PICC_IsNewCardPresent())
        return;
      if (rfid.PICC_ReadCardSerial()) {
        for (byte i = 0; i < 4; i++) {
          faculty_tag += rfid.uid.uidByte[i];
        }
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
          Serial.println(name[pos]);
          delay(2000);
          myfile = SD.open("attendance.csv", FILE_WRITE);
          data = name[pos] + "," + UID[pos];
          myfile.println(data);
          Serial.println("WROTE IN FILE SUCCESSFUL");
          myfile.close();
          digitalWrite(RELAY_PIN, LOW);
          ;
          delay(6000);
          digitalWrite(RELAY_PIN, HIGH);
        } else {
          Serial.print("Who Tf is You ?");
          Serial.println(tag);
          delay(2000);
        }
        tag = "";
        faculty_tag="";
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
      }
    } else {
      Serial.println("invalid");
    }
  }
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