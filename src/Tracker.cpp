#include "vex.h"
#include "iostream"
#include "robot-config.h"
#include "Tracker.h"
#include "constants.h"
#include "PID.h"

using namespace vex;

extern Assist Assistant;

Tracker::Tracker(motor_group & LeftDrive, motor_group & RightDrive, inertial & Inertial, rotSub & Axial, rotSub & Axial2, rotSub & Lateral, bool mirrored):
m_LeftDrive(LeftDrive),
m_RightDrive(RightDrive),
m_Inertial(Inertial),
m_Axial(Axial),
m_Axial2(Axial2),
m_Lateral(Lateral),
m_Mirrored(mirrored),
m_X(0),
m_Y(0),
m_Running(false),
m_LastAxial(0),
m_LastLateral(0),
m_LastAngle(0) {}

void Tracker::set(double setX, double setY, double setA) {
  SingleLock sl(m_Mutex);
  if(setA != 361) {
    m_Inertial.setRotation(setA, degrees);
    m_SetRotation = setA;
    setRotation = m_SetRotation;
    
    m_LastAngle = getRotation();
  }
  /* m_LastAxial = 0;
  m_Axial.setPosition(0, degrees);
  m_Axial2.setPosition(0, degrees);*/

  m_X = setX;
  m_Y = setY;
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

void Tracker::ArcIntegral() {
  SingleLock sl(m_Mutex);
  Assistant.Run();

  // Get changes in axial and lateral movement
  double axial = getAxial();
  double lateral = getLateral();

  //std::cout<<axial<<" "<<lateral<<" "<<getRotation()<<std::endl;

  double deltaAxial = axial - m_LastAxial;
  double deltaLateral = lateral - m_LastLateral;


  // Calculate heading info
  double angle = getRotation();
  double radians = (angle + m_LastAngle) * PI / 360.0; // average heading
  double deltaRadians = (angle - m_LastAngle) * PI / 180.0;

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

  m_LastAxial = axial;
  m_LastLateral = lateral;
  m_LastAngle = angle;
}

int Tracker::TrackingThread(void * pVoid) {
  Tracker * pThis = (Tracker * ) pVoid;
  do {
    pThis -> ArcIntegral();
    vex::task::sleep(10);
  } while (pThis -> Running());
  return 0;
}