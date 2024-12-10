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
lastDetected(0),
stall(true),
mode(0),
loadDeg(36),//25
armPID(PID(0.8,3,0.02,30)) {}

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

void Tracker::Integral() { //LEGACY
  SingleLock sl(m_Mutex);

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
  RunIntake();
  
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
  m_X += localY * cos(radians) * (1 - m_Mirrored * 2);;
  m_Y += localY * sin(radians);
  m_X += localX * -sin(radians) * (1 - m_Mirrored * 2);;
  m_Y += localX * cos(radians);
}

//note that automatic intake functioning is also found in DriverController.cpp
void Tracker::RunIntake() {
  // Handle arm movement and positioning
  double target = 340; //340
  if(abs(mode) == 1) {
    target = loadDeg;
  } else if(mode == 0) {
    target = 0;
  }

  if(mode == 2 && Controller1.ButtonY.pressing()) {
    target == 370;
  } else if(fabs(ArmRot.position(degrees)) >= target - 50 && mode == 2) {
    Arm.stop();
    mode = 1;
    target = loadDeg;
  }

  if(fabs(ArmRot.position(degrees)) < loadDeg - 5 && mode == 0) {
    Arm.stop(vex::brakeType::coast);
  } else if(fabs(ArmRot.position(degrees) - loadDeg) < 5 && mode == 1) {
    Arm.stop(vex::brakeType::hold);
  } else {
    double error = target - ArmRot.position(degrees);
    if(fabs(error) < 15 && mode == -1) {
      mode = abs(mode);
      intakeStop();
      intakeFwd();
    }
    
    double out = armPID.calculate(error, 0.005);
    out = std::min(std::max(out, -100.0), 100.0) * (3.0/25.0);
    
    if(out >= 0) {
      Arm.spin(forward, out, vex::voltageUnits::volt);
    } else {
      Arm.spin(reverse, -out, vex::voltageUnits::volt);
    }
  }

  // Intake control logic
  const bool armLoad = ArmRot.position(degrees) > loadDeg - 20;
  const int color = Optical.hue();
  const bool wrongColor = (m_Mirrored && color <= 30) || (!m_Mirrored && (color > 180 && color < 240));

  if(!forw && !back) {
    counter = 12;
    return;
  }

  // Handle counter updates and anti-stall logic
  if(counter == -33 || counter == -15 || (IntakeB.velocity(pct) != 0 && counter > 0)) {
    counter = armLoad ? 4 : 12;
  } else if(counter == -6 && armLoad) {
    counter = -16;
  } else if(counter == -32 && armLoad) {
    intakeStop();
    return;
  } else {
    counter -= 0.5;
  }

  // Control intake motor based on conditions
  if((forw && counter > 0) || (counter <= -16 && counter > -26 && armLoad)) {
    double deg = fmod(Intake.position(degrees), 48977.0 / 31.0);
    const bool atSortingPosition = (fabs(deg - 271) < 10 || fabs(deg - 808) < 10 || fabs(deg - 1324.2) < 10);
    
    if(colorSort > 0 && atSortingPosition) {
      if(colorSort == 2 || (colorSort == 1 && !wrongColor)) {
        colorSort--;
        Intake.spin(reverse, 6, vex::voltageUnits::volt);
        counter = -25;
      }
    } else {
      if(colorSort == -1) {
        Intake.spin(forward, 12, vex::voltageUnits::volt);
      } else if(wrongColor) {
        if(colorSort == 1 && !lastDetected) {
          colorSort++;
        } else {
          colorSort = 1;
        }
        lastDetected = true;
      } else {
        lastDetected = false;
        Intake.spin(forward, 12, vex::voltageUnits::volt);
      }
    }
  } else if(counter <= 0 && counter > -20 && stall) {
    Intake.spin(forward, 0, vex::voltageUnits::volt);
  } else if(armLoad && counter < 4) {
    Intake.spin(reverse, 4, vex::voltageUnits::volt);
  } else {
    Intake.spin(reverse, 12, vex::voltageUnits::volt);
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