#pragma once

#include <time.h>

class ScopedTimer
{
  private :
    struct timespec _init;
    double& _elapsed;
    clockid_t _clock;
  public :
    ScopedTimer(double& e_time, clockid_t clock);
    ~ScopedTimer();
};
    
#include "scoped_timer.hxx"
