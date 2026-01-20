#ifndef __MCL__
#define __MCL__

#include "Tracker.h"
#include <vector>
#include <cmath>
#include <random>

using namespace vex;

inline double deg2rad(double deg) { return deg * M_PI / 180.0; }
inline double rad2deg(double rad) { return rad * 180.0 / M_PI; }

// map objects
struct Circle { 
    double x, y, r; 
    Circle(double X, double Y, double R): x(X), y(Y), r(R) {} 
};

struct Segment { 
    double x1, y1, x2, y2; 
    Segment(double X1, double Y1, double X2, double Y2): x1(X1), y1(Y1), x2(X2), y2(Y2) {} 
};

// sensor with values relative to robot pose
struct Sensor {
    double dx, dy;
    double angleDeg;
    Sensor(double X=0, double Y=0, double A=0): dx(X), dy(Y), angleDeg(A) {}
};

// particle
struct Pose {
    double x, y, headingDeg, weight;
    Pose(double X=0, double Y=0, double H=0): x(X), y(Y), headingDeg(H), weight(1.0) {}
};

class MCL {
private:
    Tracker &tracker;
    vex::task* mclTask = nullptr;
    std::vector<Pose> particles;
    std::vector<Circle> circles;
    std::vector<Segment> segments;
    Sensor sensor;

    Pose adjustedDeadReckoning = Pose(0, 0, 90);

    bool running = false;
    double lastAxial;
    double lastLateral;
    double lastAngleDeg;
    int numParticles;
    double sensorSigma;
    double maxDist;
    

    std::default_random_engine rng;
    std::normal_distribution<double> posNoise = std::normal_distribution<double>(0.0, 0.02);
    std::normal_distribution<double> resampleNoise = std::normal_distribution<double>(0.0, 0.12);

    void adjustDeadReckoning();
    void UpdateParticles();
    void StepMCL();
    double expectedMeasurement(const Pose &p) const;
    double raycastDistance(double ox, double oy, double angleDeg) const;
    bool rayCircle(double ox, double oy, double dx, double dy, const Circle &c, double &tOut) const;
    bool raySegment(double ox,double oy,double dx,double dy,const Segment &s,double &tOut) const;
    void resampleParticles();

    static int MCLThread(void *pVoid);

public:
    MCL(Tracker &t, int nParticles=1000, Sensor s=Sensor(), double sigma=2.0, double maxD=40.0)
        : tracker(t), numParticles(nParticles), sensor(s), sensorSigma(sigma), maxDist(maxD)
    {
        rng.seed(0);
        initMap();
        initParticles(0, 0, 90);
    }

    void initParticles(double x, double y, double headingDeg) {
        std::normal_distribution<double> noise(0.0, 0.2);
        particles.clear();
        for (int i = 0; i < numParticles; i++) {
            particles.emplace_back(x + noise(rng), y + noise(rng), headingDeg);
        }
        adjustedDeadReckoning.x = x;
        adjustedDeadReckoning.y = y;
        adjustedDeadReckoning.headingDeg = headingDeg;
    }

    void initMap() {
        segments.emplace_back(0,0,144,0);
        segments.emplace_back(144,0,144,144);
        segments.emplace_back(144,144,0,144);
        segments.emplace_back(0,144,0,0);

        circles.emplace_back(24,2.5,2.5);
        segments.emplace_back(26.828,48,24,50.828);
        segments.emplace_back(24,50.828,21.172,48);

        circles.emplace_back(24,141.5,2.5);
        segments.emplace_back(26.828,96,24,93.172);
        segments.emplace_back(24,93.172,21.172,96);

        circles.emplace_back(120,2.5,2.5);
        segments.emplace_back(117.172,48,120,50.828);
        segments.emplace_back(120,50.828,122.828,48);

        circles.emplace_back(120,141.5,2.5);
        segments.emplace_back(117.172,96,120,93.172);
        segments.emplace_back(120,93.172,122.828,96);

        segments.emplace_back(71.646,69.172,69.172,71.646);
        segments.emplace_back(74.828,72.354,72.354,74.828);
    }

    void Start() {
        if (!running) {
            running = true;
            lastAxial = tracker.getAxial();
            lastLateral = tracker.getLateral();
            lastAngleDeg = tracker.getHeading();
            initParticles(tracker.getX(),tracker.getY(),lastAngleDeg);

            if (!mclTask) mclTask = new vex::task(MCLThread, this);
        }
    }



    void Stop() { running = false; }
    bool Running() const { return running; }

    Pose estimatePose() const {
        double sumX=0, sumY=0, sumW=0, sumSin, sumCos;
        for (auto &p : particles) {
            sumW += p.weight;
            sumX += p.x * p.weight;
            sumY += p.y * p.weight;
            sumSin += sin(deg2rad(p.headingDeg)) * p.weight;
            sumCos += cos(deg2rad(p.headingDeg)) * p.weight;
        }

        if(sumW <= 0 || particles.size() == 0) return Pose();

        return Pose(sumX/sumW, sumY/sumW, rad2deg(atan2(sumSin/sumW, sumCos/sumW)));
    }

    double getX(bool weightedAverage = false) {
        if(weightedAverage) return estimatePose().x;
        return adjustedDeadReckoning.x;
    }

    double getY(bool weightedAverage = false) {
        if(weightedAverage) return estimatePose().y;
        return adjustedDeadReckoning.y;
    }

    void setOdomX(double x) {
        adjustedDeadReckoning.x = x;
    }

    void setOdomY(double y) {
        adjustedDeadReckoning.y = y;
    }

    const std::vector<Pose> &getParticles() const { return particles; }
};

#endif