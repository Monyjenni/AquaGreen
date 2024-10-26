#include <ESP8266WiFi.h> // Include the ESP8266 WiFi library

// Replace with your network credentials
const char* ssid = "LET STORE";
const char* password = "LET@2022";

void setup() {
  // Start the Serial communication
  Serial.begin(115200);
  delay(10);

  // Print the WiFi SSID and Password
  Serial.println("WiFi Credentials:");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);

  // Connect to WiFi
  Serial.println("\nConnecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait until the board connects to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print the IP address
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing in loop
}
