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

    String messages[] = {
    "DST        ",
    "Tara        ",
    "Carry me    ",
    "I'm a Wigfrid"
  };

  for(int i = 0; i<4; i++)
  {
    lcd.setCursor(0,1);
    lcd.print(messages[i]);
    delay(1000);

    lcd.clear();
  }

/* for(int i = 0; i<= 10; i++)
{
  lcd.setCursor(0,1);
  lcd.print(i);
  delay(1000);
} */
/*   lcd.setCursor(0,1);
  lcd.print("Wilson");
  delay(1000);
  lcd.print("Willow");
  delay(1000);
  lcd.print("Wolfgang");
  delay(1000);
  lcd.print("Wendy");
  delay(1000);
  lcd.print("Woodie");
  delay(1000);
  lcd.print("Maxwell");
  delay(1000);
  lcd.print("Webber");
  delay(1000);
  lcd.print("Wigfried");
  delay(1000); */
}
