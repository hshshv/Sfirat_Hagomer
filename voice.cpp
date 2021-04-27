#include "voice.h"

voice::voice(int trackID, double duration_)
{
  id = trackID;
  duration = duration_;
}

int voice::ID()
{
  return (id);
}

double voice::Duration()
{
  return (duration);
}
