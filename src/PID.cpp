#include "vex.h"
#include "iostream"
#include "PID.h"

PID::PID(double p, double i, double d): kP(p), kI(i), kD(d), prevError(0), integral(0), prevD(0), counter(1) {}

void PID::start(double error) {
  integral = 0;
  prevD = 0;
  prevError = error;
  counter = 1;
}

double PID::calculate(double error, double dt, bool interpolate) {
  integral *= 0.99; //decay to avoid integral windup
  integral += error * dt;
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