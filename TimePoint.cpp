#include "TimePoint.h"

TimePoint::TimePoint(int Year, int Month_, int DayInMonth, int Hour, int Minute, int Second, int milliseconds)
{
  year = Year; month = Month_; day = DayInMonth; hour = Hour; minute = Minute; second = Second; millisecond = milliseconds;
  //dayOfTheWeak
}

TimePoint::TimePoint()
{
  TimePoint(0, 1, 0, 0, 0, 0, 0);
}

bool TimePoint::IsAfter(TimePoint otherDate)
{
  return (!(IsBefore(otherDate) || Equles(otherDate)));
}

bool TimePoint::IsBefore(TimePoint otherDate)
{
  if (year < otherDate.year)
    return (true);
  if (year > otherDate.year)
    return (false);

  if (month < otherDate.month)
    return (true);
  if (month > otherDate.month)
    return (false);

  if (day < otherDate.day)
    return (true);
  if (day > otherDate.day)
    return (false);

  if (hour < otherDate.hour)
    return (true);
  if (hour > otherDate.hour)
    return (true);

  if (minute < otherDate.minute)
    return (true);
  if (minute > otherDate.minute)
    return (false);

  if (second < otherDate.second)
    return (true);
  if (second > otherDate.second)
    return (false);

  if (millisecond < otherDate.millisecond)
    return (true);

  return (false);
}

bool TimePoint::Equles(TimePoint otherDate)
{
  if (year != otherDate.year)
    return (false);
  if (month != otherDate.month)
    return (false);
  if (day != otherDate.day)
    return (false);
  if (hour != otherDate.hour)
    return (false);
  if (minute != otherDate.minute)
    return (false);
  if (second != otherDate.second)
    return (false);
  if (millisecond != otherDate.millisecond)
    return (false);

  return (true);
}

/*
  TimePoint TimePoint::TimeUntil(TimePoint otherDate)

   בעייתי:
   אם אני מחשב את ההבדל בין העשירי לחודש הזה לבין העשירי לחודש הבא. האם יש הבדל של חודש? בהנחה וההבדל הוא 30 ימים באמת, האם להחשיב את כחודש או לא? שהרי יש חודשים יותר קצרים ויותר ארוכים.
   מסקנה: צריך לחשב את ההבדל בימים, שעות דקות וכו', כי הם תמיד באורך קבוע.

  {
  TimePoint Today(year, month, day, hour, minute, second, millisecond);
  if(otherDate.millisecond > Today.millisecond)
  {

  }
  }
*/

TimePoint TimePoint::TimeUntil(TimePoint otherDate)
{
  TimePoint today(year, month, day, hour, minute, second, millisecond);
  TimePoint result(0, 1, 0, 0, 0, 0, 0);

  if (otherDate.millisecond < today.millisecond)
  {
    otherDate.millisecond += 1000;
    --otherDate.second;
  }
  result.millisecond = otherDate.millisecond - today.millisecond;

  while (otherDate.second < today.second)
  {
    otherDate.second += 60;
    --otherDate.minute;
  }
  result.second = otherDate.second - today.second;

  while (otherDate.minute < today.minute)
  {
    otherDate.minute += 60;
    --otherDate.hour;
  }
  result.minute = otherDate.minute - today.minute;

  while (otherDate.hour < today.hour)
  {
    otherDate.hour += 24;
    --otherDate.day;
  }
  result.hour = otherDate.hour - today.hour;


  if (otherDate.month != today.month)
  {
    while (otherDate.month != today.month || otherDate.year != today.year)
    {
      result.day += (daysIn(today.month, today.year) - today.day);
      today.month += 1;
      if (today.month > 12)
      {
        ++today.year;
        today.month = 1;
      }
      today.day = 1;
    }
    result.day += otherDate.day;
  }
  else
  {
    result.day = otherDate.day - today.day;
  }
  //years!!!!!
  return (result);
}

int DaysIn[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int TimePoint::daysIn(int month, int year)
{
  --month;
  int days = DaysIn[month];
  if (month == February)
  {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
      ++days;
    }
  }
  return (days);
}
