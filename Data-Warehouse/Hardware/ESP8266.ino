#define BLYNK_TEMPLATE_ID "TMPL6CqtyYMKo"
#define BLYNK_TEMPLATE_NAME "plant watering system"
#define BLYNK_AUTH_TOKEN "1AC5i4K0AYyOEd6pp0Ud_JcUP-U-uj24"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Meisme";
char pass[] = "me200604!";

#define MOISTURE_SENSOR_PIN A0  // Pin connected to moisture sensor
#define RELAY_PIN D3            // Pin connected to relay

const int moistureThreshold = 50;

void setup() {
  Serial.begin(115200);                // Start serial communication
  pinMode(RELAY_PIN, HIGH); // Turn relay off initially (assuming low activate it)

  Serial.println("Initializing Blynk App..."); // Debug message
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);     // Start Blynk connection

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi"); // Debug message
  } else {
    Serial.println("Failed to connect to WiFi"); // Debug message
  }
}

void loop() {
  int sensorValue = analogRead(A0);  // Read analog value from sensor
  Serial.print("Moisture Level: ");
  Serial.println(sensorValue);         // Print value to Serial Monitor
  
  // Send moisture level to Blynk app
  Blynk.virtualWrite(V0, sensorValue); // Send moisture value to virtual pin V0

   // Print to Serial Monitor for debugging
  Serial.print("Sent moisture level to Blynk: ");
  Serial.println(sensorValue);  

  if (sensorValue < moistureThreshold) {
    digitalWrite(RELAY_PIN, LOW); //turn on relay 
    Serial.println("Water Pump ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Water Pump OFF");
  }
  
  delay(1000);                         // Wait 1 second between readings
  Blynk.run();                         // Run Blynk to maintain connection
}