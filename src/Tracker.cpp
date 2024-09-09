#include "vex.h"
#include "iostream"
#include "robot-config.h"
#include "Tracker.h"
#include "constants.h"
#include "PID.h"

using namespace vex;

Tracker::Tracker(motor_group & LeftDrive, motor_group & RightDrive, inertial & Inertial, rotation & Axial, rotation & Lateral, bool mirrored): m_LeftDrive(LeftDrive), m_RightDrive(RightDrive), m_Inertial(Inertial), m_Axial(Axial), m_Lateral(Lateral), m_Mirrored(mirrored), m_X(cos(oOffsetAngle * PI / 180.0) * oOffset), m_Y(sin(oOffsetAngle * PI / 180.0) * oOffset), m_Running(false), m_LastAxial(0), m_LastLateral(0), m_LastAngle(0), m_X2(cos(oOffsetAngle * PI / 180.0) * oOffset), m_Y2(sin(oOffsetAngle * PI / 180.0) * oOffset), forw(false), back(false), counter(12) {}

void Tracker::set(double setX, double setY, double setA) {
  SingleLock sl(m_Mutex);
  double ang = ((setA == 361) ? getRotation() : setA);
  m_Inertial.setRotation(ang, degrees);
  m_SetRotation = ang;
  m_LastAngle = getRotation();
  
  m_X = setX + cos((getRotation() + oOffsetAngle) * PI / 180.0) * oOffset;
  m_Y = setY + sin((getRotation() + oOffsetAngle) * PI / 180.0) * oOffset;
  
  m_X2 = m_X;
  m_Y2 = m_Y;
}

void Tracker::Start() {
  if (!m_Running) {
    SingleLock sl(m_Mutex);

    m_LeftDrive.resetPosition();
    m_RightDrive.resetPosition();
    m_Axial.resetPosition();
    m_Lateral.resetPosition();
    

    m_LastAxial = getAxial();
    m_LastLateral = getLateral();

    m_LastAngle = getRotation();
    m_Running = true;
    vex::task track(TrackingThread, this);
  }
}

void Tracker::Stop() {
  if (m_Running) {
    SingleLock sl(m_Mutex);
    m_Running = false;
  }

  WaitUntilCompleteStop();
}

void Tracker::WaitUntilCompleteStop() {
  return;
}

void Tracker::Integral() {
  SingleLock sl(m_Mutex);

  //axial movement
  double axial = getAxial();
  double aDif = axial - m_LastAxial;

  double magnitude = aDif * degreesToInches;
  double radians = (getRotation() + m_LastAngle) * PI / 360.0;
  
  m_X += cos(radians) * magnitude;
  m_Y += sin(radians) * magnitude;

  //lateral movement
  double lateral = getLateral();
  double lDif = lateral - m_LastLateral;

  double lMagnitude = lDif * oDegreesToInches;
  
  m_X += sin(radians) * lMagnitude;
  m_Y -= cos(radians) * lMagnitude;

  ArcIntegral();
  intakeStall();
  
  m_LastAxial = axial;
  m_LastLateral = lateral;
  m_LastAngle = getRotation();
}

void Tracker::ArcIntegral() {
  SingleLock sl(m_Mutex);

  //axial movement
  double axial = getAxial();
  double aDif = (axial - m_LastAxial) * degreesToInches;

  double radians = (getRotation() + m_LastAngle) * PI / 360.0;
  double deltaRadians = (getRotation() - m_LastAngle) * PI / 180.0;

  double dx = 0;
  double dy = aDif;
  
  //deltaRadians=0;

  if(deltaRadians!=0) {
    double arcRadius = aDif / deltaRadians;
    dx = cos(deltaRadians)*arcRadius-arcRadius;
    dy = sin(deltaRadians)*arcRadius;
  }
  double aMagnitude = sqrt(dx*dx+dy*dy) * ((dy<0)?-1:1); //calculating vector of movement based on arc
  double direction = deltaRadians / 2.0 + radians;
  m_X2 += cos(direction) * aMagnitude;
  m_Y2 += sin(direction) * aMagnitude;

  //lateral movement
  double lateral = getLateral();
  double lDif = lateral - m_LastLateral;

  double lMagnitude = lDif * oDegreesToInches;
  
  m_X2 += sin(radians) * lMagnitude;
  m_Y2 -= cos(radians) * lMagnitude;

  /*m_LastAxial = axial;
  m_LastLateral = lateral;
  m_LastAngle = getRotation();*/
}

void Tracker::intakeStall() {
  if(!forw && !back) {
    counter = 12;
    Intake.stop();
    return;
  } else if(counter == -30 || counter == -20 || (IntakeB.velocity(pct) != 0 && counter > 0)) {
    counter = 12;
  } else {
    counter -= 0.5;
  }

  if(forw && counter > 0) {
    int color = Optical.hue();
    if(!Optical.isNearObject()) {
      Intake.spin(forward,12,vex::voltageUnits::volt);
    } else if(autonMode != 3 && autonMode != 4 && color >= 50) {
      counter = -28;
    } else if((autonMode == 3 || autonMode == 4) && !(color > 150 && color < 210)) {
      counter = -28;
    }
  } else if (counter <= 0 && counter > -20) {
    Intake.spin(reverse,2,vex::voltageUnits::volt);
  } else {
    Intake.spin(reverse,12,vex::voltageUnits::volt);
  }
}

int Tracker::TrackingThread(void * pVoid) {
  Tracker * pThis = (Tracker * ) pVoid;
  do {
    pThis -> Integral();
    vex::task::sleep(10);
  } while (pThis -> Running());
  return 0;
}