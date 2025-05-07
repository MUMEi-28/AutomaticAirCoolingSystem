#include <Wire.h> // I2C for LCD
#include <LiquidCrystal_I2C.h> // LCD 1602 library
#include <DHT.h> // Adafruit DHT sensor library

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD object with 16cols x 2rows

// Fan pins - L298N
#define MOTOR_ENA 9
#define MOTOR_IN1 10
#define MOTOR_IN2 11

#define MOTOR_ENB 2
#define MOTOR_IN3 3
#define MOTOR_IN4 4

// DHT sensor settings
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // DHT sensor object

// Global variables
float temperature = 0;
float humidity = 0;
bool fanIsOn = false; // For hysteresis

void setup() {
  delay(500); // Boot delay

  Serial.begin(9600);
  Serial.println("DHT11 Humidity & Temperature Sensor\n\n");

  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(0,1);
  lcd.print("Humidity:");

  dht.begin(); // Initialize DHT sensor

  // Motor pins as output
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
}

void loop() {
  TemperatureHumiditySensor();
  fanLogic();
}

void TurnOnMotor() {
  analogWrite(MOTOR_ENA, 150);
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);

  analogWrite(MOTOR_ENB, 150);
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
}

void TurnOffMotor() {
  analogWrite(MOTOR_ENA, 0);
  analogWrite(MOTOR_ENB, 0);
}

void TemperatureHumiditySensor() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  PrintOnMonitor();
  DisplayStuffLcd();
  delay(2000); // Wait 2 seconds before next read
}

void PrintOnMonitor() {
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature);
  Serial.println("C");
}

void DisplayStuffLcd() {
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("% ");
}

void fanLogic() {
  if (!fanIsOn && temperature >= 35.0) {
    TurnOnMotor();
    fanIsOn = true;
  }
  else if (fanIsOn && temperature <= 30.0) {
    TurnOffMotor();
    fanIsOn = false;
  }
}
