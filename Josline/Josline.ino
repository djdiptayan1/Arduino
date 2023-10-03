//RFID PINS
// MOSI-23
// MISO-19
// SDA-21
// SCK-18
// RST-22

//LCD PINS
// SDA-33
// SCL-32

//KEYPAD
// ROWS - 15, 2, 0, 4
// COLUMNS - 16, 25, 5, 17

//GSM MODULE
// TXD
// RXD


#include <SPI.h>
#include <Wire.h>
#include <Keypad.h>
#include <unordered_map>
#include <string>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

//DISPLAY
#define scl 32
#define sda 33
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int flag;
int pos = 0;

//RFID
#define RST_PIN 22
#define SS_PIN 21
MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class
MFRC522::MIFARE_Key key;
String tag;

// OTP
String otp = "12";
String password = "";  // Variable to store the entered password
bool otpMode = false;  // Flag to indicate OTP mode

//KEYPAD
const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 15, 2, 0, 4 };
byte colPins[COLS] = { 16, 25, 5, 17 };

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//ID CARD DETAILS AND CONTACTS
std::unordered_map<std::string, std::pair<std::string, std::string>> id = {
  { "249224147101", { "Diptayan", "+919474182596" } },
  { "20115312290", { "Krrish", "+1234567890" } },
  { "105199145101", { "Ayan", "+1234567890" } },
  { "89195136101", { "Siddhima", "+1234567890" } },
  { "732146101", { "Akhil", "+1234567890" } },
  { "12146146101", { "Sanjeevini", "+1234567890" } },
  { "20124314493", { "Divya", "+1234567890" } },
  { "5714814893", { "Kannan", "+1234567890" } },
  { "2011015993", { "Anand", "+1234567890" } },
  { "2124819651", { "Roel", "+1234567890" } },
  { "24921115293", { "Hanna", "+1234567890" } },
  { "2282520551", { "Adheesh", "+1234567890" } },
  { "23318615593", { "Vijay", "+1234567890" } },
  { "24917615793", { "Rupkatha", "+1234567890" } },
  { "2057394124", { "Pranav", "+1234567890" } },
  { "25118137101", { "Siddhartha", "+1234567890" } },
  { "5710320105", { "Pracheta", "+1234567890" } },
  { "153231145101", { "Liya", "+1234567890" } },
  { "89240141101", { "Mohammed", "+918153830293" } },
  { "2497213893", { "Deempak", "+1234567890" } },
  { "2574138101", { "Sakshi", "+1234567890" } },
  { "2014320651", { "Harikrishnan", "+1234567890" } },
  { "21715214293", { "Swetanshu", "+1234567890" } },
  { "24915615993", { "Nikit", "+1234567890" } },
  { "1482420051", { "Abishek", "+1234567890" } },
  { "575515793", { "Mangalampalli", "+1234567890" } },
  { "13210921051", { "Danush", "+1234567890" } },
  { "97722105", { "Maitry", "+1234567890" } },
  { "2277414879", { "Rehana", "+1234567890" } },
  { "2519143101", { "Medhir", "+1234567890" } },
  { "16934139101", { "Daniel", "+1234567890" } },
  { "8920214593", { "Smeet", "+1234567890" } },
  { "41237136101", { "Idhant", "+1234567890" } },
  { "579813993", { "Abuzer", "+918805696853" } }
};

void setup() {
  Wire.begin(sda, scl);
  Serial.begin(115200);
  //Serial2.begin(115200);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.print("STARTING");
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522
  delay(3000);
}

void loop() {
  String enteredOTP = "";
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("scan");
  lcd.setCursor(1, 1);

  //RFID READING
  if (!rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);

    //checking using UNORDERED MAPS
    std::string find = tag.c_str();
    if (id.find(find) != id.end()) {

      //SEND MESSAGE TO THE RFID HOLDER
      String number = id[find].second.c_str();
      Serial.println(number);
      send_SMS(number, otp);

      // Reset the OTP mode flag
      otpMode = false;

      //TAKING INPUT FROM THE KEYPAD
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Enter OTP:");
      lcd.setCursor(1, 1);
      while (!otpMode) {
        enteredOTP = getinput();
        if (enteredOTP == otp) {
          flag = 1;
        }
      }
      password = "";
      enteredOTP = "";
    } else
      flag = 0;

    if (flag == 1) {
      flag = 0;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Welcome");
      lcd.setCursor(1, 1);
      String strfind = id[find].first.c_str();
      Serial.println(strfind);
      lcd.println(strfind);
      delay(2000);
    } else {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("UN-IDENTIFIED");
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

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    Serial2.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (Serial2.available()) {
    Serial.write(Serial2.read());  //Forward what Software Serial received to Serial Port
  }
}
void send_SMS(String ph_number, String otp) {
  Serial.println("AT+CMGF=1");  // Configuring TEXT mode
  updateSerial();
  String cmd = "AT+CMGS=\"" + ph_number + "\"";
  Serial.println(cmd);  //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  Serial.print(cmd);  //text content
  updateSerial();
  Serial.println();
  Serial.println("Message Sent");
  Serial.write(26);
}
String getinput() {
  char key = keypad.getKey();
  if (key) {
    if (key == 'D') {
      // If 'D' key is pressed, display the entered password and switch to OTP mode
      otpMode = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Password: ");
      lcd.setCursor(0, 1);
      lcd.print(password);
      Serial.print("Password: ");
      Serial.println(password);
    } else if (!otpMode) {
      // If not in OTP mode, add the key to the password
      password += key;
    }
  }
  return password;
}