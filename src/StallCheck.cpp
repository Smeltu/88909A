#include "vex.h"
#include "iostream"
#include "StallCheck.h"

StallCheck::StallCheck(double r, double t): rate(r), threshold(t) {}

void StallCheck::start() {
    sum = 100.0 / (1 - rate);
}

bool StallCheck::calculate(double output) {
    sum *= rate;
    sum += output;
    return fabs(sum) <= threshold;
}
