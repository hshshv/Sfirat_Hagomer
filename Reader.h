#include "arduino.h"
#include "TimePoint.h"
#include "voice.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#ifndef reder_
#define reder_

class Reader
{
  public:
    Reader(int TX, int RX);
    void Say(TimePoint timeLeft);
    //static void begin(int TX, int RX);
  private:
    void play(voice Voice);
    void play2digits(int number);
    SoftwareSerial SOS;
    DFRobotDFPlayerMini Player;
};

#endif
