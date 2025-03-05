#include "Assist.h"
#include "iostream"

using namespace vex;

Assist::Assist(bool mirrored):
m_Mirrored(mirrored),
forw(false),
back(false),
counter(12),
colorSort(0),
stall(true),//true
averageColor(0),
mode(0),
loadDeg(74),//13
armPID(PID(2.5,30,0.013,5)) {}

//note that automatic intake functioning is also found in DriverController.cpp

void Assist::gestureCheck() {
  if(!Optical.installed()) {
    return;
  }
  const bool wrongColor = (m_Mirrored && averageColor <= 80) || (!m_Mirrored && (averageColor > 100));
  std::cout<<averageDist * 100 <<", "<<averageColor<<", "<<(wrongColor?"sorting":"pass")<<std::endl;
  if (wrongColor && colorSort >= 0) {
    colorSort++;
  }
}

void Assist::scheduleCheck() {
  if(colorSort < -2) {
    colorSort++;
    return;
  }
  if(colorSort == -2) {
    intakeStop();
    colorSort = 0;
    return;
  }
}

void Assist::Run() {
  RunIntake();
  RunArm();
}

void Assist::RunIntake() {
  // Intake control logic
  const bool armLoad = fabs(armRotation()) > loadDeg - 20 && fabs(armRotation()) < loadDeg * 2;
  const int color = Optical.hue();
  averageColor = averageColor * 0.85 + color * 0.15;

  if(!forw && !back) {
    counter = 12;
    return;
  }

  /*const int dist = Distance.value();*/
  /*if(Distance.installed() && averageDist>200 && dist<=200) {
    gestureCheck();
  }*/
  
  const bool dist = Optical.isNearObject();
  if(averageDist > 0.5 && averageDist * 0.9 + dist * 0.1 <= 0.5) {
    scheduleCheck();
    gestureCheck();
  }

  //std::cout<<averageDist * 200 <<", "<<averageColor<<std::endl;

  averageDist = averageDist * 0.9 + dist * 0.1;


  // Handle counter updates and anti-stall logic
  if(counter == -33 || counter == -15 || ((IntakeA.velocity(pct) != 0 || IntakeB.velocity(pct) != 0) && counter > 0)) {
    counter = armLoad ? 5 : 12;
  } else if(counter == -4 && armLoad) {
    counter = -18;
  } else if(counter == -25 && armLoad) {
    intakeStop();
    return;
  } else if(!stall && !armLoad) {

  } else {
    counter -= 0.5;
  }
  // Control intake motor based on conditions
  if((forw && counter > 0) || (counter > -24 && counter <= -16 && armLoad)) {
    double deg = fmod(intakeRotation(), 1460.025);
    const bool atSortingPosition = (fabs(deg - 410) < 10 || fabs(deg - 1110) < 10); //414
    if(atSortingPosition && colorSort > 0) {
      colorSort--;
      Intake.spin(reverse, 6, vex::voltageUnits::volt);
      counter = -25;
    } else {
      Intake.spin(forward, 12, vex::voltageUnits::volt);
    }
  } else if(armLoad && counter <= -24) {
    Intake.spin(forward, 1, vex::voltageUnits::volt);
  } else if((armLoad && counter < 4) || (counter <= 0 && counter > -20)) {
    Intake.spin(reverse, 3, vex::voltageUnits::volt);
  } else {
    if(!back && !forw) {
      return;
    }
    Intake.spin(reverse, 12, vex::voltageUnits::volt);
  }
}

void Assist::RunArm() {
  double pos = armRotation();
  //pos = fabs(pos);

  // Handle arm movement and positioning
  bool pressing = Controller1.ButtonY.pressing();
  double target = 440; //- pressing * 0;
  if(abs(mode) == 1) {
    target = loadDeg;
  } else if(mode == 0) {
    target = -200;
  } else if(mode == 2) {
    if(!pressing && armB.update(pos-target,0.01)) {
      Arm.stop();
      mode = 1;
      target = loadDeg;
    }
  } else if(mode == 3) {
    target = 650;
    if(!pressing && pos >= target - 17) {
      Arm.stop();
      mode = 0;
      target = 0;
    }
  } else if(mode >= 4) {
    target = mode;
  }

  if(pos < 20 && mode == 0) {
    Arm.stop(vex::brakeType::coast); //coast
  } else if(fabs(pos - loadDeg) < 1 && mode == 1) {
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

void Assist::resetAfterAuton() {
  Arm.spin(forward, 0, vex::voltageUnits::volt);
  Arm.resetPosition();
  armPID.start(0);
}
