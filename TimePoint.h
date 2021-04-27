#include "Arduino.h"
#include "enumim.h"

#ifndef TimePoint_
#define TimePoint_

class TimePoint
{
  public:
    TimePoint(int Year, int Month_, int DayInMonth, int Hour, int Minute, int Second, int milliseconds);
    TimePoint();
    int year;
    int month;
    int day;
    Day dayOfTheWeak;
    int hour;
    int minute;
    int second;
    int millisecond;

    bool IsAfter(TimePoint otherDate);
    bool IsBefore(TimePoint otherDate);
    bool Equles(TimePoint otherDate);
    TimePoint TimeUntil(TimePoint); //TimePoint maby is not thw most fitting term here, since the difference is not a point in time but a quantity of time.
    //the TimeUntil returns the time in days + hours + minutes + seconds + milliseconds, in the format of TimePoint, although it is not a time point: there is no time such as 89/0/0, 20:13:15.
    int daysIn(int month, int year);
  private:
    //int daysIn(int month, int year);
    subtractMillis(int num);
};

#endif
