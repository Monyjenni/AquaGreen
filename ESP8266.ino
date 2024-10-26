
#define RELAY_PIN D3   // Pin connected to the relay
#define MOISTURE_SENSOR_PIN A0  // Pin connected to the moisture sensor

void setup() {
  Serial.begin(9600);            // Start serial communication
  pinMode(RELAY_PIN, OUTPUT);    // Set the relay pin as an output
  digitalWrite(RELAY_PIN, HIGH); // Turn off the relay initially (HIGH for active low relay)
}

void loop() {
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);  // Read analog value from sensor
  Serial.print("Moisture Level: ");
  Serial.println(sensorValue);                            // Print value to Serial Monitor

  // Control relay based on moisture level
  if (sensorValue < 300) { // Adjust this threshold based on your testing
    digitalWrite(RELAY_PIN, LOW); // Turn on the water pump (activating the relay)
    Serial.println("Water Pump ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn off the water pump (deactivating the relay)
    Serial.println("Water Pump OFF");
  }

  delay(1000); // Wait 1 second between readings
}