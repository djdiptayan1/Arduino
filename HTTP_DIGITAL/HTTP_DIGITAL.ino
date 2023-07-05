#include <WiFi.h>

const char* ssid = "VENKATESWARLLU";
const char* password = "9494638071";

const char* serverIP = "192.168.1.14"; // Replace with the Flask API's IP address
const int serverPort = 80; // Replace with the appropriate port number

WiFiClient client;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print ESP32 IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read digital input from a pin
  int digitalValue = 100; // Replace with the appropriate digital pin

  // Prepare HTTP GET request with the digital value
  String request = "GET /updateData?digital=" + String(digitalValue); // Replace with the appropriate endpoint and query parameter
  request += " HTTP/1.1\r\nHost: " + String(serverIP) + "\r\nConnection: close\r\n\r\n";

  // Make the request to the server
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connected to server");
    client.print(request);
    Serial.println("Request sent");
  } else {
    Serial.println("Connection failed");
  }

  // Wait for server response
  while (client.connected() && !client.available()) {}

  // Read and print the server response
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.println();

  // Close the connection
  client.stop();

  delay(2000); // Adjust the delay based on your needs
}
