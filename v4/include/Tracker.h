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
  double m_X;
  double m_Y;
  bool m_Running;
  double m_LastAxial;
  double m_LastLateral;
  double m_LastAngle;
  double m_SetRotation;
  double m_X2;
  double m_Y2;
  
  public: Tracker(motor_group & LeftDrive, motor_group & RightDrive, inertial & Inertial, rotation & Axial, rotation & Lateral);
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
    return fmod(getRotation(),360.0);
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
};

#endif