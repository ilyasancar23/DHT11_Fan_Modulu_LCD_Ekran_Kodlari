#include "DHT.h"
#define RELAY_FAN_PIN A5 
#define DHTPIN 8           
#define DHTTYPE DHT11
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);//RS,EN,D4,D5,D6,D7

const int TEMP_THRESHOLD_UPPER = 25; 
const int TEMP_THRESHOLD_LOWER = 20; 

DHT dht(DHTPIN, DHTTYPE);

float temperature;    

void setup()
{
  Serial.begin(9600); 
  dht.begin();        
  pinMode(RELAY_FAN_PIN, OUTPUT); 
  lcd.begin(16, 2);
}

void loop()
{
  // wait a few seconds between measurements.
  delay(2000);

  temperature = dht.readTemperature();;  // read temperature in Celsius
  
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    
lcd.setCursor(0, 1);
lcd.print("Sicaklik =" );
lcd.print((float)temperature, 8);

    if(temperature > TEMP_THRESHOLD_UPPER){
      Serial.println("The fan is turned on");
    
      digitalWrite(RELAY_FAN_PIN, HIGH); // turn on
    } else if(temperature < TEMP_THRESHOLD_LOWER){
      Serial.println("The fan is turned off");
      digitalWrite(RELAY_FAN_PIN, LOW); // turn on
    }
  }
}