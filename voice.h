#include "arduino.h"

#ifndef voice_
#define voice_

class voice
{
  public:
    voice(int trackID, double duration_);
    int ID();
    double Duration();
  private:
    int id;
    double duration;
};

#endif
