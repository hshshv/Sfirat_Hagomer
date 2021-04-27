#include <Wire.h>
#include "RTClib.h"
#include "LC.h"
#include "TimePoint.h"
#include "Sensors.h"
#include "Reader.h"

#define changeModeEvery 10
#define ReadingButtonInput 5

Button SummerClock(3);
RTC_DS1307 Clock;
LC LCD(0x3F, 16, 2); //0x68 / 0x50
//Reader reader(3, 2); //TX, RX//dont uncomment it until you solved the 0x62 problem

//////////////////////////////////////////
TimePoint goal(2021, 5, 3, 18, 22, 10, 0);
//////////////////////////////////////////

enum modes : unsigned byte
{
  showDate, showDaysLeft, Reading, modesNum
};

modes mode = showDate;

void setup()
{
  LCD.begin();
  LCD.backlight();
  LCD.setCursor(0, 0);

  Serial.begin(9600);
  Serial.println("starting");

  LCD.print("starting");
  if (! Clock.begin())
  {
    LCD.print("RTC dissconected");
    Serial.println("dissconnected");
    while (true) {}
  }

  if (! Clock.isrunning())
  {
    LCD.print("RTC eror");
    LCD.setCursor(0, 1);
    LCD.print("resetting date");
    Serial.println("reset");
    Clock.adjust(DateTime(2021, 4, 26, 11, 10, 0));
    delay(2000);
  }
  Serial.println("finneshed setup");
  LCD.clear();
  //Clock.adjust(DateTime(2021, 4, 27, 16, 36, 15));
}


DateTime now;
int lastSecond;
String daysOfTheWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int changeModeInZero = changeModeEvery;

void loop()
{
  while (now.second() == lastSecond)
  {
    now = Clock.now();
  }

  lastSecond = now.second();
  --changeModeInZero;
  if (!changeModeInZero)
  {
    changeModeInZero = changeModeEvery;
    nextMode();
  }
  if (mode == showDate)
  {
    showDateTime(now);
  }
  if (mode == showDaysLeft)
  {
    ShowDaysLeft(TimeLeft(now));
  }
}

void DoIdelTasks()
{
  if (digitalRead(ReadingButtonInput))
  {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Reading time");
//    reader.Say(TimeLeft(now));
    nextMode();
  }
}

/*
   לעשות שכל פעם יכתוב רק את מה שהתחדש. כלומר ישמור עותק של המצב הנוכחי, ורק אם משהו השתנה אז יכתוב אותו
*/
void showDateTime(DateTime now)
{
  LCD.setCursor(0, 0);

  LCD.print(daysOfTheWeek[now.dayOfTheWeek()]);
  byte i = 8;
  printDigits(i, 0, now.hour());
  LCD.setCursor(i + 2, 0);
  LCD.print(":");
  printDigits(i + 3, 0, now.minute());
  LCD.setCursor(i + 5, 0);
  LCD.print(":");
  printDigits(i + 6, 0, now.second());

  i = 0;
  printDigits(0, 1, now.day());
  LCD.setCursor(i + 2, 1);
  LCD.print("/");
  printDigits(i + 3, 1, now.month());
  LCD.setCursor(i + 5, 1);
  LCD.print("/");
  LCD.setCursor(i + 6, 1);
  LCD.print(now.year());
}

void ShowDaysLeft(TimePoint now)
{
  LCD.setCursor(0, 0);
  while (GetTheNumOfDigitsOfInt(now.day) > 4)
  {
    now.day = 10 * floor(now.day / 10);
  }
  LCD.print(now.day);
  LCD.setCursor(GetTheNumOfDigitsOfInt(now.day), 0);
  LCD.print(" days and ");
  printDigits(0, 1, now.hour);
  LCD.setCursor(2, 1);
  LCD.print(":");
  printDigits(3, 1, now.minute);
  LCD.print(":");
  printDigits(6, 1, now.second);
  LCD.setCursor(8, 1);
  LCD.print(" left");
}
/*
  Serial.print("today: ");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(",  ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());
*/


void printDigits(uint8_t Xlocation, uint8_t Ylocation, int number)
{
  LCD.setCursor(Xlocation, Ylocation);
  if (number < 10)
  {
    LCD.print("0");
    LCD.setCursor(Xlocation + 1, Ylocation);
  }
  LCD.print(number);
}

void nextMode()
{
  mode = 1 - mode;//switching between 'showDate' and 'showDaysLeft'
  LCD.clear();
}

int GetTheNumOfDigitsOfInt(int theInt)
{
  theInt = abs(theInt);
  if (theInt < 100000 && theInt >= 10000)
  {
    return (5);
  }
  if (theInt < 10000 && theInt >= 1000)
  {
    return (4);
  }
  if (theInt < 1000 && theInt >= 100)
  {
    return (3);
  }
  if (theInt < 100 && theInt >= 10)
  {
    return (2);
  }
  if (theInt < 10)
  {
    return (1);
  }
}

TimePoint TimeLeft(DateTime now)
{
  TimePoint today(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second(), 0);
  return (today.TimeUntil(goal));
}
