#include <Wire.h>
#include "LQ.h"
#include "virtuabotixRTC.h"

#define ChangingTime 10000
//{year, month, day, hour, minute, second}
int today[] = {2020, 9, 8, 23, 27, 32};
int goal[] = {2020, 10, 22, 5, 17, 29};
int Difference[] = {0, 0, 0, 0, 0, 0};

int Units[] = {1, 12, 0, 24, 60, 60};
int DaysInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
String Month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
String Day[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

LQ screen(0x3F, 16, 2);
virtuabotixRTC myRTC(6, 7, 8); //clk = 6

void setup()
{
  screen.begin();
  screen.backlight();
  Serial.begin(9600);
  Serial.print("the num of digits in 12345 is: ");
  Serial.println(GetTheNumOfDigitsOfInt(12345));
  Serial.begin(9600);
  Serial.print("goal: ");
  printArray(goal, 6);
  Serial.print("today: ");
  printArray(today, 6);
  Diff(today, goal);
  Serial.print("Diff: ");
  printArray(Difference, 6);
  //Serial.print("step 1 dif: ");
  //printArray(Diff(today, goal), 6);
  //Serial.println(TodayIsBiggerThenGoal(today, goal, 0));
  //Serial.println(TodayIsBiggerThenGoal(goal, today, 0));

  Serial.println();
}

int daysLeft;
int WKSLeft;

void loop()
{
  inputeDateOfToday();
  Diff(today, goal);
  daysLeft = GetDays();
  
  ShowTodaysDate();
  delay(ChangingTime);
  screen.clear();

  ShowGeneralTime();
  delay(ChangingTime);

  screen.clear();

  for (int i = 0; i < floor(ChangingTime / 250); ++i)
  {
    inputeDateOfToday();
    ShowExectTime();
    delay(ChangingTime / floor(ChangingTime / 250));
  }
  screen.clear();
}

int todaysDayOfTheWeek;
void ShowTodaysDate()
{
  //todaysDayOfTheWeek = myRTC.dayofweek;
  todaysDayOfTheWeek = 2;
  //screen.setCursor(0, 0);
  //screen.print("Today: ");
  screen.setCursor(0, 0);
  screen.print(Day[todaysDayOfTheWeek - 1]);
  screen.setCursor(Day[todaysDayOfTheWeek - 1].length(), 0);
  screen.print(",");
  screen.setCursor(screen.XCursor + 2, 0);
  screen.print(today[2]);
  screen.setCursor(screen.XCursor + GetTheNumOfDigitsOfInt(today[2]) + 1, 0);
  screen.print("on");
  screen.setCursor(0, 1);
  screen.print(Month[today[1] - 1]);
  screen.setCursor(Month[today[1] - 1].length(), 1);
  screen.print(", ");
  screen.setCursor(Month[today[1] - 1].length() + 2, 1);
  screen.print(today[0]);
}

void ShowGeneralTime()
{
  //screen.clear();
  screen.setCursor(0, 0);
  screen.print(daysLeft);
  screen.setCursor(GetTheNumOfDigitsOfInt(daysLeft) + 1, 0);
  screen.print("days left:");
  screen.setCursor(0, 1);
  WKSLeft = floor(daysLeft / 7);
  screen.print(WKSLeft);
  screen.setCursor(GetTheNumOfDigitsOfInt(WKSLeft) + 1, 1);
  screen.print("WKS, ");
  screen.setCursor(screen.XCursor + 5, 1);
  screen.print(daysLeft % 7);
  screen.setCursor(screen.XCursor + 2, 1);
  screen.print("days");
}

void ShowExectTime()
{
  screen.setCursor(0, 0);
  screen.print(daysLeft);
  screen.setCursor(GetTheNumOfDigitsOfInt(daysLeft) , 0);
  screen.print(" days, ");
  screen.setCursor(7 + screen.XCursor , 0);
  screen.print(Difference[3]);//max 2 digits
  screen.setCursor(screen.XCursor + GetTheNumOfDigitsOfInt(Difference[3]) , 0);
  screen.print(" HRS");
  screen.setCursor(0, 1);
  screen.print(Difference[4]);
  screen.setCursor(GetTheNumOfDigitsOfInt(Difference[4]) , 1);
  screen.print(" min, ");
  screen.setCursor(6 + screen.XCursor , 1);
  screen.print(Difference[5]);
  screen.setCursor(screen.XCursor + GetTheNumOfDigitsOfInt(Difference[5]) , 1);
  screen.print(" sec.");
  Serial.print("days: "); Serial.print(daysLeft);
  Serial.print(" | hours: "); Serial.print(Difference[3]);
  Serial.print(" | minutes: "); Serial.print(Difference[4]);
  Serial.print(" | seconds: "); Serial.print(Difference[5]);
  Serial.println();
}

int GetFloor(float num)
{
  int sofla = floor(num);
  return (sofla);
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

void inputeDateOfToday()
{
  /*
    myRTC.updateTime();
    today[0] = myRTC.year;
    today[1] = myRTC.month;
    today[2] = myRTC.dayofmonth;
    today[3] = myRTC.hours;
    today[4] = myRTC.minutes;
    today[5] = myRTC.seconds;
  */
}

int GetDays()//according to 'Differnce' and 'taody' and 'goal'
{
  int sum = 0;
  sum += 365 * (Difference[0]);
  for (int i = today[0]; i < today[0] + Difference[0]; i++)
  {
    if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0))
    {
      sum++;
      i += 4;
    }
  }

  int thisMonth;
  for (int i = 0; i < Difference[1]; i++)
  {
    thisMonth = today[1] + i;
    if (thisMonth < 1)
    {
      thisMonth += 12;
    }
    sum += DaysInMonths[thisMonth];
    if (thisMonth == 1 && today[0] % 4 == 0 && (today[0] % 100 != 0 || today[0] % 400 == 0))
    {
      sum++;
    }
  }

  sum += Difference[2];

  return (sum);
}

void Diff(int today[], int goal[])
{
  int dif[6];
  for (int i = 0; i < 6; i++)
  {
    dif[i] = goal[i] - today[i];
  }
  // printArray(dif, 6);
  //int finaldiff[6];
  for (int i = 5; i >= 0; i--)
  {
    if (dif[i] < 0)
    {
      Serial.print("dif[");
      Serial.print(i);
      Serial.println("] < 0");
      --dif[i - 1];
      if (i == 2)
      {
        Difference[i] = dif[i] + daysInThisMonth(goal[1] - 1 , goal[0]);
      }
      else
      {
        Difference[i] = dif[i] + Units[i];
      }
    }
    else
    {
      Difference[i] = dif[i];
    }
  }
  /*
    Serial.print("final dif: ");
    printArray(finaldiff, 6);
  */
}


bool TodayIsBiggerThenGoal(int* tod, int* goal, int index)
{
  if (tod[index] > goal[index])
  {
    return (true);
  }

  if (tod[index] < goal[index] || (tod[index] == goal[index] && index == 5))
  {
    return (false);
  }

  return (TodayIsBiggerThenGoal(tod, goal, index + 1));
}

int daysInThisMonth(int month, int year)
{
  if (month == 1 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
  {
    return (29);
  }
  else
  {
    return (DaysInMonths[month]);
  }
}

void printArray(int harry[], int leng)
{
  Serial.print("{");
  Serial.print(harry[0]);
  for (int i = 1; i < leng; i++)
  {
    Serial.print(", ");
    Serial.print(harry[i]);
  }
  Serial.println("}");
}
/*
  int WhatIsTheSize(int harry[])
  {
  int i;
  try
  {
    for (i = 0; true; ++i)
    {
      if (harry[i] == harry[i]){}
    }
    throw;
  }
  catch ()
  {
    return (i);
  }
  }
*/
