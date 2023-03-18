#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SD.h>

#define SS_PIN 10
#define RST_PIN 9

constexpr uint8_t cs = D8;//NODE MCU

File myfile;

char *UID[] = {"UID 1", "UID 2", "UID 3", "UID 4", "UID 5", "UID 6"};
byte lock = 0;
String name;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  SPI.begin();
  rfid.PCD_Init();

  //CREATING A FILE NAMED ATTENDANCE
  if(!SD.begin(cs)){ //nodeMCU
    Serial.println("SD CARD initialization failed");
    while(1);
  }
  Serial.println("initialization DONE");
  
  if (SD.exists("attendance.txt")) {
    Serial.println("attendance.txt exists.");
  } else {
    Serial.println("attendance.txt doesn't exist.");
  }
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");

  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (!rfid.PICC_ReadCardSerial())
    return;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scanning");
  Serial.print("NUID tag is :");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    lcd.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();


  for (int i = 0; i < 6; i++)
    if (ID.substring(1) == UID[i] && lock == 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door is locked");
      delay(15);
      lcd.clear();
      lock = 1;
    } 
    else if (ID.substring(1) == UID[i] && lock == 1 ) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Door is open");
      delay(15);
      lcd.clear();
      lock = 0;
        if(ID=="UID 1")
          name="";
        else if(ID=="UID 2")
          name="";
        else
          name="Invalid";
      //writing into SD card
      myfile = SD.open("attendance.txt", FILE_WRITE);
      myfile.print(ID);
      myfile.print("\t");
      myfile.println(name);
      Serial.println("WROTE IN FILE SUCCESSFUL");
      myfile.close();
    } 
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong card!");
      delay(1500);
      lcd.clear();
    }
}