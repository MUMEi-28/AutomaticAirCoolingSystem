#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LCD 1602 library
#include "dht.h" // DHT11 temp & humid sensor library
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Define fan pins
#define fanPin 5
#define DIRA 3
#define DIRB 4

// Sensor
dht DHT;
#define DHT_PIN 7 // DHT11 data pin

// Global variables
float temperature = 0;
float humidity = 0;

void setup() {
  // put your setup code here, to run once:

  // Fan ititialize
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor

  //LCD STUFFS
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(0,1);
  lcd.print("Humidity:");                            


  // FAN INITTIALZIE
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, HIGH);
   pinMode(DIRA,OUTPUT);

  pinMode(DIRB,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


}
void TemperatureHumiditySensor()
{
   temperature = DHT.temperature; 
   humidity = DHT.humidity; 

  DHT.read11(DHT_PIN); // Get pin 7
  
  // PRINTING LANG KASI WALA LCD
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature); 
  Serial.println("C  ");
  
  delay(5000);//Wait 5 seconds before accessing sensor again.

}

void TESTING()
{
  for(int i = 0; i <= 5; i++)
  {
    temperature++;
    delay(1000);

    // LCD STUFFS
    lcd.setCursor(0,0);
    lcd.print("Temp: " );
    lcd.print(temperature);

    lcd.setCursor(0, 1);
    lcd.print("Humidity: " );
  }
}

void fanLogic()
{

   // FAN LOGIC
  if(temperature >= 5.0)
  {
    digitalWrite(fanPin, HIGH);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);

  }
  else
  {
    digitalWrite(fanPin, LOW);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
  } 
}
