#include "vex.h"
#include "iostream"
#include "robot-config.h"
#include "Tracker.h"
#include "constants.h"
#include "PID.h"

using namespace vex;

extern Assist Assistant;

Tracker::Tracker(motor_group & LeftDrive, motor_group & RightDrive, inertial & Inertial, rotation & Axial, rotation & Axial2, rotation & Lateral, bool mirrored):
m_LeftDrive(LeftDrive),
m_RightDrive(RightDrive),
m_Inertial(Inertial),
m_Axial(Axial),
m_Axial2(Axial2),
m_Lateral(Lateral),
m_Mirrored(mirrored),
m_X(cos(oOffsetAngle * PI / 180.0) * oOffset),
m_Y(sin(oOffsetAngle * PI / 180.0) * oOffset),
m_Running(false),
m_LastAxial(0),
m_LastLateral(0),
m_LastAngle(0),
m_X2(cos(oOffsetAngle * PI / 180.0) * oOffset),
m_Y2(sin(oOffsetAngle * PI / 180.0) * oOffset) {}

void Tracker::set(double setX, double setY, double setA) {
  SingleLock sl(m_Mutex);
  double ang = ((setA == 361) ? getRotation() : setA);
  m_Inertial.setRotation(ang, degrees);
  m_SetRotation = ang;
  m_LastAngle = getRotation();
  double temp = getAxial();
  m_Axial.setPosition(temp, degrees);
  m_Axial2.setPosition(temp, degrees);

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
    m_Axial2.resetPosition();
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

void Tracker::Integral() { // LEGACY
  SingleLock sl(m_Mutex);
  Assistant.Run();

  //axial movement
  double axial = getAxial();
  double aDif = axial - m_LastAxial;

  double magnitude = aDif * degreesToInches;
  double radians = (getRotation() + m_LastAngle) * PI / 360.0;
  
  m_X2 += cos(radians) * magnitude * (1 - m_Mirrored * 2);
  m_Y2 += sin(radians) * magnitude;

  //lateral movement
  double lateral = getLateral();
  double lDif = lateral - m_LastLateral;

  double lMagnitude = lDif * oDegreesToInches;
  
  m_X2 += sin(radians) * lMagnitude * (1 - m_Mirrored * 2);
  m_Y2 -= cos(radians) * lMagnitude;

  ArcIntegral();
  
  m_LastAxial = axial;
  m_LastLateral = lateral;
  m_LastAngle = getRotation();
}

void Tracker::ArcIntegral() {
  SingleLock sl(m_Mutex);

  // Get changes in axial and lateral movement
  double axial = getAxial();
  double lateral = getLateral();
  double deltaAxial = (axial - m_LastAxial) * degreesToInches;
  double deltaLateral = (lateral - m_LastLateral) * oDegreesToInches;

  // Calculate heading info
  double radians = (getRotation() + m_LastAngle) * PI / 360.0; // average heading
  double deltaRadians = (getRotation() - m_LastAngle) * PI / 180.0;

  // Calculate local x and y coordinates
  double localX = 0;
  double localY = 0;
  if (deltaRadians == 0) {
    localX = deltaLateral;
    localY = deltaAxial;
  } else {
    localX = 2 * sin(deltaRadians / 2) * (deltaLateral / deltaRadians);
    localY = 2 * sin(deltaRadians / 2) * (deltaAxial / deltaRadians);
  }

  // Update global posixtion
  m_X += localY * cos(radians) * (1 - m_Mirrored * 2);
  m_Y += localY * sin(radians);
  m_X += localX * -sin(radians) * (1 - m_Mirrored * 2);
  m_Y += localX * cos(radians);
}

int Tracker::TrackingThread(void * pVoid) {
  Tracker * pThis = (Tracker * ) pVoid;
  do {
    pThis -> Integral();
    vex::task::sleep(10);
  } while (pThis -> Running());
  return 0;
}