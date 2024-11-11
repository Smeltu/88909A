#ifndef __PID__
#define __PID__

class PID {
  private: double kP,
  kI,
  kD,
  windupRange,
  prevError,
  integral,
  prevD,
  counter;

  public: PID(double p, double i, double d, double windup = 0);
  void start(double error);
  double calculate(double error, double dt = 0.005, bool interpolate = true);
  double get(char val) {
    if(val=='p'){
      return kP;
    } else if(val=='i') {
      return kI;
    } else if(val=='d') {
      return kD;
    }
    return -1.0;
  }
};

#endif