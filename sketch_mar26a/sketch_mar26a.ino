#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("G");
  lcd.setCursor(0,1);
  lcd.print("DST");
}

void loop() {
  // put your main code here, to run repeatedly:

}
