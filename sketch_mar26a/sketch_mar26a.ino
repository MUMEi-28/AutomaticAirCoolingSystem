#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Define fan pins
#define fanPin 5
#define DIRA 3
#define DIRB 4
void setup() {
  // put your setup code here, to run once:

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

  float temperature = 25.0; // temporary value
  float humidity = 33.0; // temporary value

// TESTING PURPOSES
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
