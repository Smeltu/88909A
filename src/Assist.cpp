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
averageColor(38),
intakeMode(0) {}

//note that automatic intake functioning is also found in DriverController.cpp

void Assist::gestureCheck() {
  if(!Optical.installed()) {
    return;
  }
  const bool wrongColor = (m_Mirrored && averageColor <= 1.2) || (!m_Mirrored && (averageColor > 1.7));
  //std::cout<<colorSort<<std::endl;
  if (wrongColor && colorSort >= 0) {
    //std::cout<<averageDist * 200 <<", "<<averageColor<<", sorting"<<std::endl;
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
    colorSort = -1 * (autonMode == 7); //note: colorsort is off
    return;
  }
}

void Assist::Run() {
  RunIntake();
}

int a = 0;
void Assist::RunIntake() {
  // Intake control logic
  const int color = Optical.hue();
  averageColor = averageColor * 0.9 + log10(fmax(1,color - 15)) * 0.1;

  if(!forw && !back) {
    counter = 20;
    return;
  }
  
  /* const bool dist = Optical.isNearObject();

  if(averageDist >= 0.3) {
    if(newRing == -1) {
      scheduleCheck();
      newRing = 0;
    } else if(newRing == 0) {
      gestureCheck();
    }
  }

  if(averageDist <= 0.1 && newRing > -1) {
    if(newRing != 1) {
      //std::cout<<averageDist * 200 <<", "<<averageColor<<", pass"<<std::endl;
    }
    averageDist = 0;
    newRing = -1;
  }

  averageDist = averageDist * 0.9 + dist * 0.1;*/

  if(counter == -10 || ((IntakeA.velocity(pct) != 0 || IntakeB.velocity(pct) != 0) && counter > 0 && counter <= 20)) {
    counter = 20;
  } else if(counter > 20) {
    counter -= 0.1;
  } else if(stall) {
    counter -= 0.5;
  }

  // Control intake motor based on conditions
  if((forw && counter > 0)) {
    if(counter > 20 && counter <= 36) {
      Intake.spin(forward, fmax(8, counter / 3.0), vex::voltageUnits::volt);
    } else {
      Intake.spin(forward, 12, vex::voltageUnits::volt);
    }
  } else {
    Intake.spin(reverse, 12, vex::voltageUnits::volt);
  }
}
