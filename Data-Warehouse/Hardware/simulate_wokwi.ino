#include <DHTesp.h>
#include <WiFi.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>

#define pinDht 15
DHTesp dhtSensor;

#define WIFI_AP "Wokwi-GUEST"
#define WIFI_PASS ""

#define TB__SERVER "demo.thingsboard.io"
#define TOKEN "m539cza3sEgnRj12Kxqr"

constexpr uint16_t MAX_MESSAGE_SIZE = 128U;

WiFiClient espClient;
Arduino_MQTT_Client mqttClient(espClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);

void connectToWifi()
{
  Serial.println("Connecting to WIFI...");
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20)
  {
    WiFi.begin(WIFI_AP, WIFI_PASS, 6);
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("\nFailed to connect to WiFi.");
  }
  else
  {
    Serial.println("\nConnected to WiFi");
  }
}

void connectToThingsBoard()
{
  if (!tb.connected())
  {
    Serial.println("Connect to thingsboard server");

    if (!tb.connect(TB__SERVER, TOKEN))
    {
      Serial.println("Failed to connect to Thingsboard");
    }
    else
    {
      Serial.println("Connected to Thingsboard");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  dhtSensor.setup(pinDht, DHTesp::DHT22);
  connectToWifi();
  connectToThingsBoard();
}

void loop()
{
  connectToWifi();

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temp = data.temperature;
  int hum = data.humidity;

  Serial.println(temp);
  Serial.println(hum);
  if (!tb.connected())
  {
    connectToThingsBoard();
  }
  delay(10); // speeds up simulation
  tb.loop();
}
