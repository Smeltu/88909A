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
int c = -1;

//arm
double mode = 0;
double loadDeg = 140;//215
PID armPID = PID(0.25,0.25,0);

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
    if(Hook.value()) {
      theTracker.intakeStop();
      theTracker.intakeRev();
      c = 30;
    }
  }
  triggered = false;
}

void runEndgame() {
  Endgame.set(!Endgame.value());
}

void toggleColorSort() {
  theTracker.toggleSort();
}

void armToggle() {
  theTracker.toggleArm();
}

void armScore() {
  theTracker.scoreArm();
}

void toggleDoinker() {
  Doinker.set(!Doinker.value());
}

int x = 0;
bool antiStall() {
  x++;
  return x > 100;
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
  Controller1.ButtonY.pressed(armScore);
  Controller1.ButtonB.pressed(armToggle);
  Controller1.ButtonRight.pressed(toggleDoinker);

  theTracker.Start();
  Auton.Init(0,0,0);
  if(autonMode == 7) {
    Prop.set(false);
    Auton.DriveStraight(3,361,50,20,false,antiStall);
    intakeForward();
    Auton.DriveStraight(-3,361,20,20,false,antiStall);
  }
  while (true) {
    RunDriveTrain();
    RunHook();
    if(i==0) {
      //std::cout<<"rot: "<<ArmRot.position(degrees)<<std::endl;
      //std::cout<<Optical.hue()<<" "<<Optical.isNearObject()<<" "<<counter<<std::endl;
      std::cout<<theTracker.getX()<<", "<<theTracker.getX2()<<"; "<<theTracker.getY()<<", "<<theTracker.getY2()<<std::endl;
      //std::cout<<theTracker.getRotation()<<" "<<theTracker.getHeading()<<std::endl;
      //std::cout<<Axial.position(degrees)<<" "<<Axial2.position(degrees)<<std::endl;
      //std::cout<<Intake.position(degrees)<<std::endl;
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
  if(c>=0) {
    c--;
    if(c==0) {
      theTracker.intakeStop();
    }
  }

  /*double dist = Distance.objectDistance(vex::distanceUnits::mm);
  if(dist > 65 && dist < 75 && !Hook.value() && Controller1.ButtonL1.pressing()) {*/
  if(HookLimit.PRESSED && Controller1.ButtonL1.pressing()) {
    toggleHook();
    triggered = true;
  }
}