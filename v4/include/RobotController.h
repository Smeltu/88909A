#ifndef __RobotController__
#define __RobotController__

#include "vex.h"
#include <list>
#include "SingleLock.h"
#include "Tracker.h"
#include "PID.h"
#include "StallCheck.h"

typedef void( * Event)();
typedef bool Trigger();

#define EVENT_COUNT 1000

class RobotController {
  private: motor_group & m_LeftDrive;
  motor_group & m_RightDrive;
  Tracker & m_Tracker;
  double TargetAngle(double dX, double dY, double Angle);

  // Event handling member and functions
  vex::mutex m_csEvent;
  std::list < Event > m_lstEvent;
  void AddEvent(Event evt);
  Event GetEvent();
  static int EventHandlingRoutine(void * );

  public: RobotController(motor_group & LeftDrive, motor_group & RightDrive, Tracker & theTracker);
  void Goto(double X, double Y, double AngleCalibrate = 0, bool Forward = true, Trigger StopTrigger = NULL, Event RotationEvent = NULL, double EventAngle = 0, Event StraightMovingEvent = NULL, double EventDistance = 0);
  void Output(double leftPct, double rightPct);
  void RotateTo(double TargetAngle, Event RotationEvent = NULL, double EventAngle = 0);
  void DriveStraight(double Distance, double targetHeading = 361, double maxSpeed = 100, double minSpeed = 20, bool angLimit = false, Trigger StopTrigger = NULL, Event StraightMovingEvent = NULL, double EventDistance = 0);
  void DriveArc(double X, double Y, bool Forward = true, double maxSpeed = 100, double minSpeed = 20, Trigger StopTrigger = NULL, Event positionEvent = NULL, double EventAngle = 0, Event StraightMovingEvent = NULL, double EventDistance = 0);
  void StopMotors();
  void LockWheels();
  void Init(double X0, double Y0, double Angle0) {
    m_Tracker.set(X0, Y0, Angle0);
    m_Tracker.Start();
  }
  double angleError(double a) {
    double headingError = fmod(a - m_Tracker.getHeading(), 360);
    if (headingError > 180.0) {
      headingError -= 360.0;
    }
    if (headingError < -180.0) {
      headingError += 360.0;
    }
    return (headingError);
  }
  double range(double val, double min = 0.0, double max = 100.0) {
    bool neg = val < 0;
    val = fabs(val);
    val = fmax(fmin(max, val), min);
    return (val * (neg ? -1 : 1));
  }
};

#endif