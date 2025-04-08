#include <Wire.h> // I2C for LCD
#include <LiquidCrystal_I2C.h> // LCD 1602 library
#include "dht.h" // DHT11 temp & humid sensor library
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD object with 16cols x 2rows

// Define fan pins
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
}

void loop() {
  // put your main code here, to run repeatedly:

  TemperatureHumiditySensor();

/* TurnOnMotor(); */

  fanLogic();
}

void TurnOnMotor()
{
  analogWrite(MOTOR_ENA, 150); // analog to, pede magkaroon ng discrete values[0-255]. if trippings then add speed control (:
  // 150 value lang muna, malakas ikot masyado ng 255 nililipad buong motor fan HAHAHHAHAHHA

  digitalWrite(MOTOR_IN1, HIGH); // Pampaikot ng motor, forward direction
  digitalWrite(MOTOR_IN2, LOW); // IDK, pero ayaw gumana kung wala to
}

void TemperatureHumiditySensor()
{
/*   delay(1000);//Wait before accessing Sensor
 */
  DHT.read11(DHT_PIN); // Read data on pin 7

  temperature = DHT.temperature; // Read temp
  humidity = DHT.humidity;  // Set humidity

  // Print sa monitor, nasira din LCD e
  PrintOnMonitor();
;
  
  delay(2000);//Wait 5 seconds MAXIMUM 2SEC, idk what happens if less than that and am not willing to find out.
DisplayStuffLcd();
}
void PrintOnMonitor()
{
    // PRINTING LANG KASI WALA LCD [DITO NA PRINT SERIAL MONITOR YUNG SERIAL BEGIN SA TAAS]
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature); 
  Serial.println("C  ");
}

void DisplayStuffLcd()
{
   // LCD STUFFS
    lcd.setCursor(0,0);
    lcd.print("Temp: " );
    lcd.print(temperature);
    lcd.print("C" );

    // walang print line e, ayaw din mag concatenate
    lcd.setCursor(0, 1);
    lcd.print("Humidity: " );
    lcd.print(humidity);
    lcd.print("%" );
}

void TESTING() // Testing ng sensor kasi nasira, kunwari sensor to
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
  if(temperature >= 40.0) // Wag 30c, default 30c temp pag gabi e. tas 35c naman tanghali GG
  {
    TurnOnMotor();
  }
  else
  {
    analogWrite(MOTOR_ENA, 0); // turn fan off
  } 
}
