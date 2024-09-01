#include "vex.h"
#include "iostream"
#include "BreakTimer.h"

BreakTimer::BreakTimer(double r, double t): range(r), time(t), curr(0) {}

bool BreakTimer::update(double error, double dt) {
    curr += dt;
    curr *= fabs(error) < fabs(range);
    return curr > time;
}
