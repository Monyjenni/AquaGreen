#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BLYNK_TEMPLATE_ID "TMPL6CqtyYMKo"
#define BLYNK_TEMPLATE_NAME "plant watering system"
#define BLYNK_AUTH_TOKEN "1AC5i4K0AYyOEd6pp0Ud_JcUP-U-uj24"
#define BLYNK_PRINT Serial

// Wi-Fi credentials
char ssid[] = "Meisme";
char pass[] = "me200604!";

// MQTT settings for ThingsBoard
const char* mqtt_server = "demo.thingsboard.io";  // ThingsBoard MQTT server
const int mqtt_port = 1883;                        // MQTT port
const char* accessToken = "u1M2pfyA7aCxwoSlLmTj"; // Replace with your ThingsBoard device token

WiFiClient espClient;
PubSubClient client(espClient);

#define MOISTURE_SENSOR_PIN A0  // Pin connected to moisture sensor
#define RELAY_PIN D3            // Pin connected to relay

const int moistureThreshold = 50;

void setup() {
  Serial.begin(115200);                // Start serial communication
  pinMode(RELAY_PIN, HIGH); // Turn relay off initially (assuming low activates it)

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.println("Connecting to ThingsBoard...");
    if (client.connect("ESP8266", accessToken, NULL)) {
      Serial.println("Connected to ThingsBoard");
    } else {
      Serial.print("Failed to connect, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);  // Read moisture sensor value
  Serial.print("Moisture Level: ");
  Serial.println(sensorValue);                         // Print value to Serial Monitor

  // Send moisture level to Blynk app
  Blynk.virtualWrite(V0, sensorValue);

  // Publish moisture level to ThingsBoard
  String moistureData = String(sensorValue);
  client.publish("v1/devices/measured/soilMoisture", moistureData.c_str());

  // Print to Serial Monitor for debugging
  Serial.print("Sent moisture level to ThingsBoard: ");
  Serial.println(sensorValue);

  // Control relay based on moisture level
  if (sensorValue < moistureThreshold) {
    digitalWrite(RELAY_PIN, LOW); // Turn on relay
    Serial.println("Water Pump ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn off relay
    Serial.println("Water Pump OFF");
  }

  delay(1000); // Wait 1 second between readings
  Blynk.run(); // Run Blynk to maintain connection
  client.loop(); // Maintain MQTT connection to ThingsBoard
}
