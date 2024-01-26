#include "BluetoothSerial.h"
const char *pin = "1234";  // Change this to a more secure PIN.
String device_name = "ESP32-BT";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
char response = 0;

// RELAY PINS
#define NUM_RELAYS 4
int relayPins[NUM_RELAYS] = { 1, 2, 3, 4 };
bool relayStates[NUM_RELAYS] = { false, false, false, false };

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);  // Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
#ifdef USE_PIN
  SerialBT.setPin(pin);
  Serial.println("Using PIN");
#endif

  for (int i = 0; i < NUM_RELAYS; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    response = SerialBT.read();
    Serial.println(response);
  }

  switch (response) {
    case '1':
      toggleRelay(0);
      break;
    case '2':
      toggleRelay(1);
      break;
    case '3':
      toggleRelay(2);
      break;
    case '4':
      toggleRelay(3);
      break;
    default:
      // Turn off all relays if an unsupported command is received
      turnOffAllRelays();
  }
}

void toggleRelay(int relayIndex) {
  if (relayIndex >= 0 && relayIndex < NUM_RELAYS) {
    relayStates[relayIndex] = !relayStates[relayIndex];
    digitalWrite(relayPins[relayIndex], relayStates[relayIndex] ? HIGH : LOW);
  }
  if (relayStates[relayIndex] == HIGH)
    Serial.println("ON");
  else
    Serial.println("OFF");
}

void turnOffAllRelays() {
  for (int i = 0; i < NUM_RELAYS; i++) {
    digitalWrite(relayPins[i], LOW);
    relayStates[i] = false;
  }
}
