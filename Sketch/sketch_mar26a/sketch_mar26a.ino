#include <Wire.h> // I2C for LCD
#include <LiquidCrystal_I2C.h> // LCD 1602 library
#include "dht.h" // DHT11 temp & humid sensor library
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD object with 16cols x 2rows

// Define fan pins
#define fanPin 5
#define DIRA 3 // Motor spin direction A
#define DIRB 4// Motor spin direction B 

// L298N DC motor pins
#define MOTOR_ENA 9
#define MOTOR_IN1 10
#define MOTOR_IN2 11

// Sensor
dht DHT; // DHT object
#define DHT_PIN 7 // DHT11 data pin connected to pin 7

// Global variables
float temperature = 0;
float humidity = 0;

void setup() {
  // put your setup code here, to run once:

  delay(500);//Delay to let system boot

  // Initialize serial communication with to sensor
  Serial.begin(9600);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");

 //LCD STUFFS
  Wire.begin(); // I2C communication
  lcd.init(); // init LCD
  lcd.backlight(); // turn on LCD
  lcd.setCursor(0,0);  // move to col 0 and row 0
  lcd.print("Temp:"); // print temp
  lcd.setCursor(0,1); // move to col 0, row 1
  lcd.print("Humidity:"); // print        

  // FAN INITTIALZIE
  pinMode(fanPin, OUTPUT); // set to output 
  digitalWrite(fanPin, HIGH); // default state is high 
  pinMode(DIRA,OUTPUT); // set to output 
  pinMode(DIRB,OUTPUT); // set to output 
}

void loop() {
  // put your main code here, to run repeatedly:

//  TemperatureHumiditySensor();
TurnOnMotor();
}

void TurnOnMotor()
{
  analogWrite(MOTOR_ENA, 255); // analog to, pede magkaroon ng discrete values. if trippings then add speed control (:
  digitalWrite(MOTOR_IN1, HIGH); // Pampaikot ng motor, forward direction
  digitalWrite(MOTOR_IN2, LOW); // IDK, pero ayaw gumana kung wala to
}

void TemperatureHumiditySensor()
{
  delay(1000);//Wait before accessing Sensor

   temperature = DHT.temperature; // Read temp
   humidity = DHT.humidity;  // Set humidity

  DHT.read11(DHT_PIN); // Read data on pin 7
  
  // PRINTING LANG KASI WALA LCD [DITO NA PRINT SERIAL MONITOR YUNG SERIAL BEGIN SA TAAS]
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature); 
  Serial.println("C  ");
  
  delay(5000);//Wait 5 seconds MAXIMUM 2SEC, idk what happens if less than that and am not willing to find out.

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
    digitalWrite(fanPin, HIGH); // turn fan on
    digitalWrite(DIRA, HIGH); // set motor direction 
    digitalWrite(DIRB, LOW); // idk

  }
  else
  {
    digitalWrite(fanPin, LOW); // turn fan off
  } 
}
