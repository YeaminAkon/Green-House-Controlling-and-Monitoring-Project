#include <Servo.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Pin Definitions ---
#define DHTPIN 2              // DHT11 sensor
#define DHTTYPE DHT11
#define SOIL_PIN A1           // Soil Moisture (Analog)
#define LDR_PIN A0             // LDR (Digital Read)
#define PUMP_RELAY 7          // Relay for motor
#define FAN_RELAY 8           // Relay for fan
#define LIGHT_PIN 6           // Light (LED or bulb)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust 0x27 if needed

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(SOIL_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  
  pinMode(PUMP_RELAY, OUTPUT);
  pinMode(FAN_RELAY, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("WLC EcoTechGrow");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilValue = analogRead(SOIL_PIN);
  int ldrValue = analogRead(LDR_PIN); // 0 = Dark, 1 = Bright
  

  // Display on Serial Monitor
  Serial.print("Temp: "); Serial.print(temperature); Serial.print("C ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.print("% ");
  Serial.print("Soil: "); Serial.print(soilValue); Serial.print(" ");
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  Serial.print("Light: "); Serial.println(ldrValue <400 ? "Dark" : "Bright");
 


  // Display on LCD
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C H:");
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("Soil:");
  lcd.print(soilValue);
  lcd.print(" L:");
  lcd.print(ldrValue < 400 ? "D" : "B");



  // Fan control (Temp > 32)
   digitalWrite(FAN_RELAY, temperature > 28 ? LOW : HIGH);


  //Water pump control (Soil dry)
  digitalWrite(PUMP_RELAY, soilValue > 700 ? LOW : HIGH);
  

  // Light control (Turn ON if dark)
   digitalWrite(LIGHT_PIN, ldrValue < 400 ? HIGH : LOW);
   
   

  delay(1000);
}
