#include <Wire.h>
#include "LQ.h"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LQ lcd(0x3F, 16, 2);

void setup()
{
  //Wire.begin();
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("bla bla bla bla");
  lcd.setCursor(0, 1); //(x, y) שורה אחת זו השורה למטה משום מה
  lcd.print("to to to to to");
  //lcd.backlight();
}

void loop()
{

}
