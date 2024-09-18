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


//hook
bool triggered = false;

//callbacks

void intakeForward() {
  theTracker.intakeFwd();
}

void intakeBackward() {
  theTracker.intakeRev();
}

void toggleProp() {
  Prop.set(!Prop.value());
}

void toggleHook() {
  if(!triggered) {
    Hook.set(!Hook.value());
  }
  triggered = false;
}

void runEndgame() {
  Endgame.set(!Endgame.value());
}

void toggleColorSort() {
  theTracker.toggleSort();
}

DriverController::DriverController() {}

//overall run function
void DriverController::Run(vex::competition Competition) {
  Controller1.ButtonR1.pressed(intakeForward);
  Controller1.ButtonR2.pressed(intakeBackward);
  Controller1.ButtonL1.released(toggleHook);
  Controller1.ButtonL2.pressed(toggleProp);
  Controller1.ButtonUp.pressed(runEndgame);
  Controller1.ButtonDown.pressed(toggleColorSort);

  theTracker.Start();
  Auton.Init(0,0,0);

  while (true) {
    RunDriveTrain();
    RunHook();
    if(i==0) {
      //std::cout<<Optical.hue()<<" "<<Optical.isNearObject()<<" "<<counter<<std::endl;
      //std::cout<<theTracker.getX()<<", "<<theTracker.getX2()<<", "<<theTracker.getY()<<", "<<theTracker.getY2()<<std::endl;
      //std::cout<<theTracker.getHeading()<<std::endl;
    }
    i = (i+1)%100;
    vex::task::sleep(5);
  }
}

//individual component run functions

void DriverController::RunDriveTrain() {

  //get forward and turn values, multiply by 1.1 to allow for easier maxing
  double forward = fmin(Controller1.Axis3.position(percent) * 1.1, 100);
  double turn = fmin(Controller1.Axis1.position(percent) * 1.1, 100);

  //if values are small enough, do nothing
  if (fabs(forward) < 5 && fabs(turn) < 5) {
    RightDrive.stop(vex::brakeType::coast);
    LeftDrive.stop(vex::brakeType::coast);
  } else {
    RightDrive.spin(vex::forward, 3 * (forward - turn) / 25.0, vex::voltageUnits::volt);
    LeftDrive.spin(vex::forward, 3 * (forward + turn) / 25.0, vex::voltageUnits::volt);
  }
}

void DriverController::RunHook() {
  double dist = Distance.objectDistance(vex::distanceUnits::mm);
  if(dist > 65 && dist < 75 && !Hook.value() && Controller1.ButtonL1.pressing()) {
    Hook.set(true);
    triggered = true;
  }
}