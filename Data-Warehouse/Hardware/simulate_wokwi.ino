#include <DHTesp.h>

#define pinDht 15
DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  dhtSensor.setup(pinDht,DHTesp::DHT22);
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temp = data.temperature;
  int hum = data.humidity;

  Serial.println(temp);
  Serial.println(hum);
  delay(10); //speeds up simulation
}
