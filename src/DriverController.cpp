#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "DriverController.h"
#include "Tracker.h"
#include "RobotController.h"

using namespace vex;

extern Tracker theTracker;
extern RobotController Auton;

//for output
int i=0;

//intake
bool forw = false;
bool back = false;
bool isStall = false;

//arm
bool sf = false;
bool sb = false;
int counter = 0;

//callbacks

void intakeForward() {
  forw = !forw;
  back = false;
  if(forw) {
    Intake.spin(forward,12,vex::voltageUnits::volt);
  } else {
    Intake.stop();
  }
}

void intakeBackward() {
  forw = false;
  back = !back;
  if(back) {
    Intake.spin(reverse,12,vex::voltageUnits::volt);
  } else {
    Intake.stop();
  }
}

void armForward() {
  Pto.set(sf);
  sf = !sf;
  sb = false;
  if(sf) {
    Slapper.spin(forward,12,vex::voltageUnits::volt);
  } else {
    Slapper.stop();
    counter = 100;
  }
}

void armBackward() {
  Pto.set(false);
  sb = !sb;
  sf = false;
  if(sb) {
    Slapper.spin(reverse,12,vex::voltageUnits::volt);
  } else {
    Slapper.stop();
  }
}

void armUp() {
  Slapper.spinToPosition(-1100,degrees,100,vex::velocityUnits::pct,false);
}

void armDown() {
  counter = -1;
  Slapper.spinToPosition(-20,degrees,100,vex::velocityUnits::pct,false);
}


DriverController::DriverController() {}

//overall run function
void DriverController::Run(vex::competition Competition) {
  Controller1.ButtonR1.pressed(intakeForward);
  Controller1.ButtonR2.pressed(intakeBackward);
  Controller1.ButtonA.pressed(armForward);
  Controller1.ButtonB.pressed(armBackward);
  Controller1.ButtonRight.pressed(armUp);
  Controller1.ButtonDown.pressed(armDown);

  theTracker.Start();
  Auton.Init(0,0,0);

  while (true) {
    RunDriveTrain();
    RunIntake();

    if(counter > 0) {
      counter--;
      if(counter == 0) {
        Pto.set(false);
      }
    } else if(counter < 0) {
      if(!Slapper.isSpinning()) {
        Slapper.stop(coast);
        counter = 0;
      }
    }
    if(i==0) {
      //std::cout<<theTracker.getX()<<" "<<theTracker.getY()<<std::endl;
      //std::cout<<theTracker.getAxial() * oDegreesToInches<<std::endl;
      //std::cout<<theTracker.getX()<<", "<<theTracker.getX2()<<", "<<theTracker.getY()<<", "<<theTracker.getY2()<<std::endl;
      //std::cout<<theTracker.getHeading()<<std::endl;
      //std::cout<<Inertial.rotation()<<", "<<(RightDrive.position(vex::rotationUnits::deg) - LeftDrive.position(vex::rotationUnits::deg))/9.8071<<std::endl;
    } else if (i%16==0) {
      //Brain.Screen.clear();
      //Brain.Screen.drawPixel(1,1);
    }
    i = (i+1)%100;

    vex::task::sleep(5);
  }
}

//individual component run functions
int j = 0;
void DriverController::RunDriveTrain() {

  //get forward and turn values
  double forward = fmin(Controller1.Axis3.position(percent) * 1.1, 100);
  double turn = fmin(Controller1.Axis1.position(percent) * 1.1, 100);

  //if values are small enough, do nothing
  if (fabs(forward) < 5 && fabs(turn) < 5) {
    LeftDrive.stop(vex::brakeType::coast);
    RightDrive.stop(vex::brakeType::coast);
  } else {
    RightDrive.spin(vex::forward, 3 * (forward - turn) / 25.0, vex::voltageUnits::volt);
    LeftDrive.spin(vex::forward, 3 * (forward + turn) / 25.0, vex::voltageUnits::volt);
  }
}

void DriverController::RunIntake() {
  if(!(forw || back)) {
    return;
  }
  int volts = 6;
  if(Intake.velocity(pct)!=0) {
    volts = 12;
  }
  if(volts / 12 == 1 - isStall) {
    isStall = !isStall;
    std::cout<<isStall<<std::endl;
    return;
  }
  if(forw) {
    Intake.spin(forward, volts, vex::voltageUnits::volt);
  } else {
    Intake.spin(reverse, volts, vex::voltageUnits::volt);
  }
}