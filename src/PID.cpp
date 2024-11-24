#include "vex.h"
#include "iostream"
#include "PID.h"

PID::PID(double p, double i, double d, double windup): kP(p), kI(i), kD(d), windupRange(windup), prevError(0), integral(0), prevD(0), counter(1) {}

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
  if(prevError == error && interpolate) { //noUpdate
    counter++;
    return kP * error + kI * integral + kD * prevD;
  }
  double derivative = (error - prevError) / (dt * counter);
  counter = 1;
  prevError = error;
  prevD = derivative;
  //std::cout << kP * error << ", " << kI * integral << ", " << kD * derivative << ", " << kP * error + kI * integral + kD * derivative << ", " << error << std::endl;
  return kP * error + kI * integral + kD * derivative;
}