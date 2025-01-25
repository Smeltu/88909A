#include "Assist.h"
#include "iostream"

using namespace vex;

Assist::Assist(bool mirrored):
m_Mirrored(mirrored),
forw(false),
back(false),
counter(12),
colorSort(0),
stall(true),
averageColor(0),
mode(0),
loadDeg(13),//13
armPID(PID(2.4,0,0.04,17)) {}

//note that automatic intake functioning is also found in DriverController.cpp

void Assist::gestureCheck() {
  if(!Optical.installed()) {
    return;
  }
  const bool wrongColor = (m_Mirrored && averageColor <= 25) || (!m_Mirrored && (averageColor > 50));
  std::cout<<averageDist<<", "<<averageColor<<", "<<(wrongColor?180:20)<<std::endl;
  if(colorSort == -2) {
    intakeStop();
    colorSort == 0;
    return;
  }
  if (wrongColor && colorSort >= 0) {
    colorSort++;
  }
}

void Assist::Run() {
  RunIntake();
  RunArm();
}

void Assist::RunIntake() {
  // Intake control logic
  const bool armLoad = fabs(ArmRot.position(degrees)) > loadDeg - 10;
  const int color = Optical.hue();
  /*if(color > 50) {
    std::cout<<color<<std::endl;
    averageColor = 40;
  } else {
    averageColor--;
    if(averageColor < 0) {
      averageColor = 0;
    }
  }*/
  const int dist = Distance.value();
  averageColor *= 2/3.0;
  averageColor += color/3.0;

  if(Distance.installed() && averageDist>110 && averageDist*0.5+dist/2.0<=110) {
    gestureCheck();
  }

  averageDist /= 2.0;
  averageDist += dist/2.0;

  if(!forw && !back) {
    counter = 12;
    return;
  }

  // Handle counter updates and anti-stall logic
  if(counter == -33 || counter == -15 || ((IntakeA.velocity(pct) != 0 || IntakeB.velocity(pct) != 0) && counter > 0)) {
    counter = armLoad ? 4 : 12;
  } else if(counter == -6 && armLoad) {
    counter = -16;
  } else if(counter == -25 && armLoad) {
    intakeStop();
    return;
  } else {
    counter -= 0.5;
  }
  // Control intake motor based on conditions
  if((forw && counter > 0) || (counter <= -16 && armLoad)) {
    double deg = fmod(Intake.position(degrees), 1053.268817);
    const bool atSortingPosition = (fabs(deg - 181) < 10 || fabs(deg - 538.67) < 10 || fabs(deg - 882.8) < 7); //271
    if(atSortingPosition && colorSort > 0) {
      colorSort--;
      Intake.spin(reverse, 6, vex::voltageUnits::volt);
      counter = -25;
    } else {
      Intake.spin(forward, 12, vex::voltageUnits::volt);
    }
  } else if(counter <= 0 && counter > -20 && stall) {
    Intake.spin(reverse, 2, vex::voltageUnits::volt);
  } else if(armLoad && counter < 4) {
    Intake.spin(reverse, 4, vex::voltageUnits::volt);
  } else {
    Intake.spin(reverse, 12, vex::voltageUnits::volt);
  }
}

void Assist::RunArm() {
  double pos = fabs(ArmRot.position(degrees));

  // Handle arm movement and positioning
  double target = loadDeg + 124; //113
  if(abs(mode) == 1) {
    target = loadDeg;
  } else if(mode == 0) {
    target = 0;
  }

  if(mode == 2 && Controller1.ButtonY.pressing()) {
    target == 123;
  } else if(pos >= target - 17 && mode == 2) {
    Arm.stop();
    mode = 1;
    target = loadDeg; 
  }

  if(pos < loadDeg - 1.7 && mode == 0) {
    Arm.stop(vex::brakeType::coast);
  } else if(fabs(pos - loadDeg) < 1.7 && mode == 1) {
    Arm.stop(vex::brakeType::hold);
  } else {
    double error = target - pos;
    if(fabs(error) < 5 && mode == -1) {
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