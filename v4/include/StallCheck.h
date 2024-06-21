#ifndef __STALLCHECK__
#define __STALLCHECK__

class StallCheck {
  private: double rate,
  threshold,
  sum;

  public: StallCheck(double rate, double threshold);
  void start();
  bool calculate(double output);
};

#endif