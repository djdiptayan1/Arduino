#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h> // Include ArduinoJson library

const char* ssid = "DELL515";
const char* password = "12345678";
const char* serverHost = "192.168.137.34";
const uint16_t serverPort = 3000;
const char* serverPath = "/ws";

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("WebSocket disconnected");
      break;
    case WStype_CONNECTED:
      Serial.println("WebSocket connected");
      break;
    case WStype_TEXT:
      Serial.print("Received data: ");
      Serial.println((char*)payload);
      break;

      // Parse the received JSON payload
      // DynamicJsonDocument jsonDocument(1024); // Adjust the size based on your JSON data size
      // DeserializationError error = deserializeJson(jsonDocument, (const char*)payload);

      // // Check for JSON parsing errors
      // if (error) {
      //   Serial.print("JSON parsing error: ");
      //   Serial.println(error.c_str());
      // } else {
      //   // Extract individual values from the JSON
      //   int squareButton = jsonDocument["square"];
      //   int analogValue = jsonDocument["leftAnalogX"];

      //   // Now you can use the extracted values
      //   Serial.print("Received square button: ");
      //   Serial.println(squareButton);
      //   Serial.print("Received left analog X: ");
      //   Serial.println(analogValue);
      // }
      // break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  webSocket.begin(serverHost, serverPort, serverPath);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  // Your other code goes here
}
