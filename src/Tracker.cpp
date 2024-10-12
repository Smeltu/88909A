#include "vex.h"
#include "iostream"
#include "robot-config.h"
#include "Tracker.h"
#include "constants.h"
#include "PID.h"

using namespace vex;

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
m_Y2(sin(oOffsetAngle * PI / 180.0) * oOffset),
forw(false),
back(false),
counter(12),
lastDetected(0) {}

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

void Tracker::Integral() {
  SingleLock sl(m_Mutex);

  //axial movement
  double axial = getAxial();
  double aDif = axial - m_LastAxial;

  double magnitude = aDif * degreesToInches;
  double radians = (getRotation() + m_LastAngle) * PI / 360.0;
  
  m_X += cos(radians) * magnitude * (1 - m_Mirrored * 2);
  m_Y += sin(radians) * magnitude;

  //lateral movement
  double lateral = getLateral();
  double lDif = lateral - m_LastLateral;

  double lMagnitude = lDif * oDegreesToInches;
  
  m_X += sin(radians) * lMagnitude * (1 - m_Mirrored * 2);
  m_Y -= cos(radians) * lMagnitude;

  ArcIntegral();
  RunIntake();
  
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

//note that automatic intake functioning is also found in DriverController.cpp
void Tracker::RunIntake() {

  //if not running intake, reset counter and stop
  if(!forw && !back) {
    counter = 12;
    Intake.stop();
    return;
  }
  //if the counter has ticked to a reset value or the intake unstalls by itself, resume
  if(counter == -30 || counter == -15 || (IntakeB.velocity(pct) != 0 && counter > 0)) {
    counter = 12;
    //if the arm is in the loading position, have a lower jam delay before outtaking
    if(ArmRot.position(degrees) > 100) {
      counter = 4;
    }
  } else if (counter == -6 && ArmRot.position(degrees) > 100) {
    //otherwise, if antistall code has finished executing and arm is in loading position, stop intake
    forw = false;
  } else {
    //if the intake is stalled, decrement counter by a half (note that each counter is 20ms)
    counter -= 0.5;
  }

  //get color detected by optical sensor
  int color = Optical.hue();
  //if the ring color is opposite the alliance color
  bool wrongColor = ((autonMode == 3 || autonMode == 4) && color <= 30) || (autonMode != 3 && autonMode != 4  && (color > 180 && color < 240));
  
  if(forw && counter > 0) {
    //current position of the hooks in the cycle
    double deg = fmod(Intake.position(degrees), 1587.152);
    //sort and decrement sorting queue by 1 if there is a ring at the top
    if(colorSort > 0 && (fabs(deg - 285.8) < 10 || fabs(deg - 805) < 10 || fabs(deg - 1324.2) < 10)) {//282.8,802,1321.2
      if(colorSort == 2 || (colorSort == 1 && !wrongColor)) {
        colorSort--;
        Intake.spin(reverse,6,vex::voltageUnits::volt);
        counter = -22;
      }
    } else {
      //if colorSort is toggled off, ignore ring detection and run intake forward
      if(colorSort == -1) {
        Intake.spin(forward,12,vex::voltageUnits::volt);
      } else if(wrongColor) {
        //if the wrong color is detected and was not previously detected, increment sorting queue
        if(colorSort == 1 && !lastDetected) {
          colorSort++;
        } else {
          colorSort = 1;
        }
        lastDetected = true;
      } else {
        //if a ring is not detected, run intake forward
        lastDetected = false;
        Intake.spin(forward,12,vex::voltageUnits::volt);
      }
    }
  } else if (counter <= 0 && counter > -20) {
    //for antistall, spin intake reverse at half speed
    Intake.spin(reverse,6,vex::voltageUnits::volt);
  } else if(ArmRot.position(degrees) > 20) {
    //if arm is raising or raised, spin intake reverse at third speed
    Intake.spin(reverse,4,vex::voltageUnits::volt);
  } else {
    //otherwise, spin intake reverse at full speed
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