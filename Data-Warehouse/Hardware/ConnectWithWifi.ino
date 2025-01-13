#define BLYNK_TEMPLATE_ID "TMPL6CqtyYMKo"
#define BLYNK_TEMPLATE_NAME "plant watering system"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "1AC5i4K0AYyOEd6pp0Ud_JcUP-U-uj24";
char ssid[] = "Kung Fu Tea Ground Floor 5G";
char pass[] = "cambodia@168";

BlynkTimer timer;
bool Relay = 0;

#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Print a message to the Serial Monitor for debugging
  Serial.println("System Loading...");
  delay(2000); // Short delay for system loading message
  Serial.println("System Ready");
  
  // Set interval to call soilMoistureSensor() every second
  timer.setInterval(1000L, soilMoistureSensor);
}

BLYNK_WRITE(V1) {
  Relay = param.asInt();
  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
    Serial.println("Motor is ON");
  } else {
    digitalWrite(waterPump, HIGH);
    Serial.println("Motor is OFF");
  }
}

// Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);  // Send moisture value to Blynk
  Serial.print("Moisture: ");
  Serial.print(value);
  Serial.println(" %");
}

void loop() {
  Blynk.run();  // Run Blynk library
  timer.run();  // Run the Blynk timer
}
