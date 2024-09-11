#ifndef __TRACKER__
#define __TRACKER__

#include "vex.h"
#include "SingleLock.h"
#include "constants.h"
#include "PID.h"

class Tracker {
  private: vex::mutex m_Mutex;
  motor_group & m_LeftDrive;
  motor_group & m_RightDrive;
  inertial & m_Inertial;
  rotation & m_Axial;
  rotation & m_Lateral;
  bool m_Mirrored;
  double m_X;
  double m_Y;
  bool m_Running;
  double m_LastAxial;
  double m_LastLateral;
  double m_LastAngle;
  double m_SetRotation;
  double m_X2;
  double m_Y2;

  bool forw;
  bool back;
  double counter;
  
  public: Tracker(motor_group & LeftDrive, motor_group & RightDrive, inertial & Inertial, rotation & Axial, rotation & Lateral, bool mirrored);
  void set(double x, double y, double a = 361);
  double getX() {
    return (m_X - cos((getHeading() + oOffsetAngle) * PI / 180.0) * oOffset);
  }
  double getY() {
    return (m_Y - sin((getHeading() + oOffsetAngle) * PI / 180.0) * oOffset);
  }

  double getX2() {
    return (m_X2 - cos((getHeading() + oOffsetAngle) * PI / 180.0) * oOffset);
  }
  double getY2() {
    return (m_Y2 - sin((getHeading() + oOffsetAngle) * PI / 180.0) * oOffset);
  }

  void Start();
  void Stop();
  void WaitUntilCompleteStop();
  void Integral();
  void ArcIntegral();
  static int TrackingThread(void * pVoid);
  bool Running() {
    SingleLock sl(m_Mutex);
    return m_Running;
  }
  double getRotation() {
    return (m_Inertial.rotation() - m_SetRotation) * inertialCal + m_SetRotation;
  }
  double getHeading() {
    if(m_Mirrored) {
      return fmod(180 - getRotation(), 360.0);
    }
    return fmod(getRotation(),360.0);
  }
  double angleError(double a) {
    double heading = getHeading();
    double headingError = fmod(a - heading, 360);
    if (headingError > 180.0) {
      headingError -= 360.0;
    }
    if (headingError < -180.0) {
      headingError += 360.0;
    }
    if(m_Mirrored) {
      headingError *= -1;
    }
    return (headingError);
  }
  double getAxial() {
    if(m_Axial.installed()) {
      return m_Axial.position(vex::rotationUnits::deg);
    }
    return (m_LeftDrive.position(vex::rotationUnits::deg) + m_RightDrive.position(vex::rotationUnits::deg)) / 2.0;
  }
  double getLateral() {
    return m_Lateral.position(vex::rotationUnits::deg);
  }

  void intakeFwd() {
    back = false;
    forw = !forw;
  }
  void intakeRev() {
    forw = false;
    back = !back;
  }
  void intakeStall();
};

#endif