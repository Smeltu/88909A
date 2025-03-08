#include "vex.h"
#include "iostream"
#include "PID.h"

PID::PID(double p, double i, double d, double windup): kP(p), kI(i), kD(d), windupRange(windup), prevError(0), integral(0), prevD(0), counter(1) {} // Alpha for low-pass filter

void PID::start(double error) {
  integral = 0;
  prevD = 0;
  prevError = error;
  counter = 1;
}

double PID::calculate(double error, double dt, bool interpolate) {
  integral += error * dt;
  if(fabs(error) > windupRange && windupRange != 0) { //wind up range for integral
    integral = 0;
  }
  double rawDerivative = (error - prevError) / (dt * counter);
  double derivative = 0.5 * rawDerivative + (1 - 0.5) * prevD; // Low-pass filter
  if(prevError == error && interpolate) { //noUpdate
    counter++;
    derivative = prevD;
  } else {
    counter = 1;
  }
  prevError = error;
  prevD = derivative;
  if(windupRange==10) {
    //std::cout<<kP*error<<", "<<kI*integral<<", "<<kD*derivative<<", "<< kP * error + kI * integral + kD * derivative<<std::endl;
  }
  return kP * error + kI * integral + kD * derivative;
}
