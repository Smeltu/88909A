#ifndef __TRACKER__
#define __TRACKER__

#include "Assist.h"

class Tracker {
  private: vex::mutex m_Mutex;
  motor_group & m_LeftDrive;
  motor_group & m_RightDrive;
  inertial & m_Inertial;
  rotSub & m_Axial;
  rotSub & m_Axial2;
  rotSub & m_Lateral;
  bool m_Mirrored;
  double m_X;
  double m_Y;
  bool m_Running;
  double m_LastAxial;
  double m_LastLateral;
  double m_LastAngle;
  double m_SetRotation;
  
  public: Tracker(motor_group & LeftDrive, motor_group & RightDrive, inertial & Inertial, rotSub & Axial, rotSub & Axial2, rotSub & Lateral, bool mirrored);
  

  void set(double x, double y, double a = 361);

  double getX() {
    return (m_X);
  }

  double getY() {
    return (m_Y);
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
    double sum = m_Axial.getPosition() + m_Axial2.getPosition();
    double count = m_Axial.installed() + m_Axial2.installed();
    if(count == 0) {
      return (m_LeftDrive.position(vex::rotationUnits::deg) + m_RightDrive.position(vex::rotationUnits::deg)) / 2.0;
    }
    return sum / count;
  }

  double getLateral() {
    return m_Lateral.getPosition();
  }
};

#endif