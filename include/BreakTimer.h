#ifndef __BREAKTIMER__
#define __BREAKTIMER__

//timed in seconds
class BreakTimer {
  private: double range,
  time,
  curr;

  public: BreakTimer(double r, double t);
  bool update(double error, double dt = 0.01);
};

#endif