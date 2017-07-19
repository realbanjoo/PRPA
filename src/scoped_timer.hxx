#include <time.h>

inline ScopedTimer::ScopedTimer(double& e_time, clockid_t clock = CLOCK_REALTIME)
  : _elapsed(e_time), _clock(clock)
{
  clock_gettime(CLOCK_REALTIME, &_init);
}


inline ScopedTimer::~ScopedTimer()
{
  timespec now;
  clock_gettime(_clock, &now);
  _elapsed = (now.tv_sec - _init.tv_sec) *1000.0 
    + (now.tv_nsec - _init.tv_nsec) / 1000000.0; 
}



