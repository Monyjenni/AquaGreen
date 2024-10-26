/*Plant Watering System
 PP - Final Year
 */
//include the lib files
#include <LiquidCrystal_r2c.h>
#define BLynk_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Initialize the LCD display
LiquidCrystal_r2c lcd(0x27, 16, 2);
char auth[] = "";
char ssid[] = ""; //need wifi even not use LCD?
char pass[] = "";

BlynkTimer timer;
bool Relay = 0;

//Define component pins
#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  lcd.init(); //not
  lcd.backlight(); //not

  BLynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  lcd.setCursor(1,0);
  lcd.print("System Loading")
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
}
}
lcd.clear();

//call the func()
timer.setInterval(100L, soilMoistureSensor); //100L water

Blynk_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor is ON");
  } else {
    digitalWrite(waterPump, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Motor is OFF");
  }
}

//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);

  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);
  lcd.setCursor(0, 0);
  lcd.print("Moisture :");
  lcd.print(value);
  lcd.print(" ");
}

void loop() {
  Blynk.run(); //run the blynk library
  timer.run(); // Run the Blynk timer
}
  
}