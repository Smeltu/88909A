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

void toggleProp() {
  Prop.set(!Prop.value());
}

void toggleHook() {
  Hook.set(!Hook.value());
}

DriverController::DriverController() {}

//overall run function
void DriverController::Run(vex::competition Competition) {
  Controller1.ButtonR1.pressed(intakeForward);
  Controller1.ButtonR2.pressed(intakeBackward);
  Controller1.ButtonL1.pressed(toggleHook);
  Controller1.ButtonL2.pressed(toggleProp);

  theTracker.Start();
  Auton.Init(0,0,0);

  while (true) {
    RunDriveTrain();
    if(i==0) {
      std::cout<<theTracker.getX()<<", "<<theTracker.getX2()<<", "<<theTracker.getY()<<", "<<theTracker.getY2()<<std::endl;
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