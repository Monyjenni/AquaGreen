#include <DHTesp.h>
#include <WiFi.h>

#define pinDht 15
DHTesp dhtSensor;

#define WIFI_AP "Wokwi-GUEST"
#define WIFI_PASS ""

void connectToWifi() {
  Serial.println("Connecting to WIFI...");
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    WiFi.begin(WIFI_AP, WIFI_PASS, 6);
    delay(500);
    Serial.print(".");
    attempts++;

  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to WiFi.");
  } else {
    Serial.println("\nConnected to WiFi");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  dhtSensor.setup(pinDht,DHTesp::DHT22);
  connectToWifi();
}

void loop() {
  connectToWifi();

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temp = data.temperature;
  int hum = data.humidity;

  Serial.println(temp);
  Serial.println(hum);
  delay(10); //speeds up simulation
}
