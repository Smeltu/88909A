#ifndef __MCL__
#define __MCL__

#include "Tracker.h"
#include <iostream>
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
        segments.emplace_back(0.5,0.5,143.5,0.5);
        segments.emplace_back(143.5,0.5,143.5,143.5);
        segments.emplace_back(143.5,143.5,0.5,143.5);
        segments.emplace_back(0.5,143.5,0.5,0.5);

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
        double sumX=0, sumY=0, sumW=0;
        for (auto &p : particles) {
            sumW += p.weight;
            sumX += p.x * p.weight;
            sumY += p.y * p.weight;
        }

        if(sumW <= 0 || particles.size() == 0) return adjustedDeadReckoning;

        return Pose(sumX/sumW, sumY/sumW, particles.front().headingDeg);
    }

    double getVarX() {
        double varX = 0.0;
        Pose est = estimatePose();
        for (auto &p : particles) {
            double dx = p.x - est.x;
            varX += p.weight * dx * dx;
        }
        return varX;
    }

    double getVarY() {
        double varY = 0.0;
        Pose est = estimatePose();
        for (auto &p : particles) {
            double dy = p.y - est.y;
            varY += p.weight * dy * dy;
        }
        return varY;
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
        for (auto &p : particles) p.x = x;
    }

    void setOdomY(double y) {
        adjustedDeadReckoning.y = y;
        for (auto &p : particles) p.y = y;
    }

    void setTrackerToMCL() {                                                                                                             
        Pose est = estimatePose();                                                                                                                                                                                                       
        double varX = 0.0, varY = 0.0;                                                                                                   
        for (auto &p : particles) {                                                                                                      
            double dx = p.x - est.x;                                                                                                     
            double dy = p.y - est.y;                                                                                                     
            varX += p.weight * dx * dx;                                                                                                  
            varY += p.weight * dy * dy;                                                                                                  
        }                                                                                                                                
                                                                                                                                         
        const double threshold = 150.0; //arbitrary               
        std::cout << "variances: " << varX << ", " << varY << std::endl;                                               
        if (varX <= threshold || varY <= threshold) {  
            std::cout << "passed MCL confidence threshold" << std::endl;   
            double tempX = adjustedDeadReckoning.x;
            double tempY = adjustedDeadReckoning.y;
            if(varX > threshold) {
                tempX = tracker.getX();
                std::cout << "skip X" << std::endl;
            }
            if(varY > threshold) {
                tempY = tracker.getY();
                std::cout << "skip Y" << std::endl;
            }                                                                             
            tracker.set(tempX, tempY, 361);    
            std::cout << "new coords: " << tempX << ", " << tempY << std::endl;       
            /*lastAxial = 0;
            lastLateral = 0;*/ // changed tracker instead                           
        }                                                                                                                                
    }

    const std::vector<Pose> &getParticles() const { return particles; }
};

#endif