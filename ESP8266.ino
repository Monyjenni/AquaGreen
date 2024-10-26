#define BLYNK_TEMPLATE_ID "TMPL6CqtyYMKo"
#define BLYNK_TEMPLATE_NAME "plant watering system"
#define BLYNK_TEMPLATE_ID "TMPL6CqtyYMKo"
#define BLYNK_TEMPLATE_NAME "plant watering system"
#define BLYNK_AUTH_TOKEN "1AC5i4K0AYyOEd6pp0Ud_JcUP-U-uj24"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char ssid[] = "Meisme";
char pass[] = "me200604!";

void setup() {
  Serial.begin(115200);                // Start serial communication
  Serial.println("Initializing Blynk..."); // Debug message
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
  
  delay(1000);                         // Wait 1 second between readings
  Blynk.run();                         // Run Blynk to maintain connection
}