#include "MCL.h"
#include <algorithm>
#include <cmath>
#include <vex.h>

using namespace vex;

void MCL::adjustDeadReckoning() {

    Pose est = estimatePose();

    // weighted variance
    double varX = 0.0, varY = 0.0;
    for (auto &p : particles) {
        double dx = p.x - est.x;
        double dy = p.y - est.y;
        varX += p.weight * dx * dx;
        varY += p.weight * dy * dy;
    }

    const double good = 50.0;
    const double bad  = 150.0;
    double trustX, trustY;

    if (varX <= good) trustX = 1.0;
    else if (varX >= bad) trustX = 0.0;
    else trustX = (bad - varX) / (bad - good);

    if (varY <= good) trustY = 1.0;
    else if (varY >= bad) trustY = 0.0;
    else trustY = (bad - varY) / (bad - good);

    const double baseAlpha = 0.1;
    double alphaX = baseAlpha * trustX;
    double alphaY = baseAlpha * trustY;

    adjustedDeadReckoning.x += alphaX * (est.x - adjustedDeadReckoning.x);
    adjustedDeadReckoning.y += alphaY * (est.y - adjustedDeadReckoning.y);
}

void MCL::UpdateParticles() {

    double axial = tracker.getAxial();
    double lateral = tracker.getLateral();

    double deltaAxial = axial - lastAxial;
    double deltaLateral = lateral - lastLateral;

    // calculate heading info
    double angle = tracker.getRotation();
    double radians = (angle + lastAngleDeg) * PI / 360.0; // average heading
    double deltaRadians = (angle - lastAngleDeg) * PI / 180.0;

    // calculate local x and y coordinates
    double localX = 0;
    double localY = 0;

    if (deltaRadians == 0) {
        localX = deltaLateral;
        localY = deltaAxial;
    } else {
        localX = 2 * sin(deltaRadians / 2) * (deltaLateral / deltaRadians);
        localY = 2 * sin(deltaRadians / 2) * (deltaAxial / deltaRadians);
    }

    // update global posixtion
    double dx = localY * cos(radians) + localX * -sin(radians);
    double dy = localY * sin(radians) + localX * cos(radians);

    for (auto &p : particles) {
        p.x += dx + posNoise(rng);
        p.y += dy + posNoise(rng);
        p.headingDeg = angle;
    }

    adjustedDeadReckoning.x += dx;
    adjustedDeadReckoning.y += dy;
    adjustedDeadReckoning.headingDeg = angle;

    lastAxial = axial;
    lastLateral = lateral;
    lastAngleDeg = angle;
}

void MCL::StepMCL() {
    double measuredDist = Distance.objectDistance(inches);
    if(measuredDist > maxDist) measuredDist = maxDist;

    double sumW = 0;
    for (auto &p : particles) {
        double expected = expectedMeasurement(p);
        if (expected > maxDist) expected = maxDist;
        double err = expected - measuredDist;
        p.weight = exp(-0.5 * err*err / (sensorSigma*sensorSigma));
        sumW += p.weight;
    }

    if (sumW <= 0) {
        for (auto &p : particles) p.weight = 1.0 / numParticles;
    } else {
        for (auto &p : particles) p.weight /= sumW;
    }

    resampleParticles();
}

double MCL::expectedMeasurement(const Pose &p) const {
    double angle = p.headingDeg + sensor.angleDeg;
    double ox = p.x + sensor.dx * cos(deg2rad(p.headingDeg)) - sensor.dy * sin(deg2rad(p.headingDeg));
    double oy = p.y + sensor.dx * sin(deg2rad(p.headingDeg)) + sensor.dy * cos(deg2rad(p.headingDeg));
    return raycastDistance(ox, oy, angle);
}

double MCL::raycastDistance(double ox, double oy, double angleDeg) const {
    double dx = cos(deg2rad(angleDeg));
    double dy = sin(deg2rad(angleDeg));
    double best = maxDist;

    for (auto &c : circles) {
        double t;
        if (rayCircle(ox, oy, dx, dy, c, t)) best = std::min(best, t);
    }

    for (auto &s : segments) {
        double t;
        if (raySegment(ox, oy, dx, dy, s, t)) best = std::min(best, t);
    }

    return best;
}

bool MCL::rayCircle(double ox, double oy, double dx, double dy, const Circle &c, double &tOut) const {
    double fx = ox - c.x, fy = oy - c.y;
    double a = dx*dx + dy*dy;
    double b = 2*(fx*dx + fy*dy);
    double cc = fx*fx + fy*fy - c.r*c.r;
    double disc = b*b - 4*a*cc;
    if (disc < 0) return false;
    double sq = sqrt(disc);
    double t1 = (-b - sq)/(2*a);
    double t2 = (-b + sq)/(2*a);
    tOut = 1e9;
    if (t1 >= 0) tOut = t1;
    if (t2 >= 0) tOut = std::min(tOut, t2);
    return tOut < 1e9;
}

bool MCL::raySegment(double ox,double oy,double dx,double dy,const Segment &s,double &tOut) const {
    double rx = s.x2 - s.x1, ry = s.y2 - s.y1;
    double det = -dx*ry + dy*rx;
    if (fabs(det) < 1e-9) return false;
    double cx = s.x1 - ox, cy = s.y1 - oy;
    double t = (cx*(-ry) - cy*(-rx))/det;
    double u = (dx*cy - dy*cx)/det;
    if (t >= 0 && u >= 0 && u <= 1) { tOut = t; return true; }
    return false;
}

void MCL::resampleParticles() {
    std::vector<Pose> newParticles;
    newParticles.reserve(particles.size());

    // compute cumulative weights
    std::vector<double> cdf(particles.size());
    cdf[0] = particles[0].weight;
    for (size_t i = 1; i < particles.size(); i++) cdf[i] = cdf[i-1] + particles[i].weight;

    std::uniform_real_distribution<double> dist(0.0, 1.0 / particles.size());
    double r = dist(rng);
    size_t i = 0;

    // spread computation
    Pose est = estimatePose();
    double spread = 0.0;
    for (auto &p : particles) {
        double dx = p.x - est.x;
        double dy = p.y - est.y;
        spread += dx*dx + dy*dy;
    }
    spread = sqrt(spread / particles.size());
    double mult = std::min(1.0, std::max(spread, 0.25));

    for (size_t m = 0; m < particles.size(); m++) {
        double u = r + m * 1.0 / particles.size();
        while (u > cdf[i] && i < particles.size()-1) i++;
        Pose base = particles[i];
        newParticles.emplace_back(base.x + resampleNoise(rng) * mult, base.y + resampleNoise(rng) * mult, base.headingDeg);
    }

    particles = newParticles;
}


// likely add something to set tracker to MCL prediction when the calculated raydist is close to measured + low uncertainty
int MCL::MCLThread(void *pVoid) {
    MCL *pThis = (MCL*) pVoid;

    do {
        for(int i=0;i<2;i++) {
            pThis->UpdateParticles();
            task::sleep(10);
        }
        pThis->StepMCL();
        vex::task::sleep(10);
    } while (pThis->Running());

    return 0;
}
