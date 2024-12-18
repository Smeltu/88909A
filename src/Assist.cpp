#include "Assist.h"
#include "iostream"

using namespace vex;

Assist::Assist(bool mirrored):
m_Mirrored(mirrored),
forw(false),
back(false),
counter(12),
lastDetected(0),
stall(true),
mode(0),
loadDeg(36),//25
armPID(PID(1.2,0,0.012,50)) {}

//note that automatic intake functioning is also found in DriverController.cpp

void Assist::Run() {
  RunIntake();
  RunArm();
}

void Assist::RunIntake() {
  // Intake control logic
  const bool armLoad = ArmRot.position(degrees) > loadDeg - 20;
  const int color = Optical.hue();
  const bool wrongColor = (m_Mirrored && color <= 25) || (!m_Mirrored && (color > 180));

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
      if(colorSort == 2 || (colorSort == 1 && !wrongColor && lastDetected==0)) {
        colorSort--;
        Intake.spin(reverse, 6, vex::voltageUnits::volt);
        counter = -25;
      }
    } else {
      if(colorSort == -1) {
        Intake.spin(forward, 12, vex::voltageUnits::volt);
      } else if(wrongColor) {
        if(colorSort == 1 && lastDetected == 0) {
          colorSort++;
        } else {
          colorSort = 1;
        }
        lastDetected = 20;
      } else {
        if(lastDetected>0){lastDetected--;}
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

void Assist::RunArm() {
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
}