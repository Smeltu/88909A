#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "DriverController.h"
#include "Tracker.h"
#include "RobotController.h"

using namespace vex;

extern Tracker theTracker;
extern RobotController Auton;
extern Assist Assistant;

//for output
int i=0;


//hook
bool triggered = false;
int c = -1;
BreakTimer clampTime(0.5,0.05);

//callbacks

void intakeForward() {
  Assistant.intakeFwd();
}

void intakeBackward() {
  Assistant.intakeRev();
}

void toggleProp() {
  Prop.set(!Prop.value());
}

void toggleHook() {
  if(!triggered) {
    Hook.set(!Hook.value());
    if(Hook.value()) {
      Assistant.intakeStop();
      Assistant.intakeRev();
      c = 30;
    }
  }
  triggered = false;
}

void runEndgame() {
  Endgame.set(!Endgame.value());
}

void toggleColorSort() {
  Assistant.toggleSort();
}

void toggleStallCode() {
  Assistant.toggleStall();
}

void armToggle() {
  Assistant.toggleArm();
}

void armScore() {
  Assistant.scoreArm();
}

void toggleDoinker() {
  if(Doinker.value()) {
    DoinkerClaw.set(false);
  }
  Doinker.set(!Doinker.value());
}

void toggleDoinkerClaw() {
  DoinkerClaw.set(!DoinkerClaw.value());
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
  //Controller1.ButtonL2.pressed(toggleProp);
  //Controller1.ButtonUp.pressed(runEndgame);
  Controller1.ButtonDown.pressed(toggleColorSort);
  Controller1.ButtonDown.pressed(toggleStallCode);
  Controller1.ButtonY.pressed(armScore);
  Controller1.ButtonB.pressed(armToggle);
  Controller1.ButtonRight.pressed(toggleDoinker);
  //Controller1.ButtonL2.pressed(toggleDoinkerClaw);

  theTracker.Start();
  Auton.Init(0,0,0);

  Doinker.set(false);

  if(autonMode == 7) {
    Assistant.intakeFwd();
    Auton.DriveStraight(1.5,361,15,15);
    wait(100,msec);
  }
  while (true) {
    RunDriveTrain();
    RunHook();
    if(i==90) {
      Brain.Screen.clearLine();
    }
    if(i==0) {
      //std::cout<<"rot: "<<ArmRot.position(degrees)<<std::endl;
      //std::cout<<Optical.hue()<<" "<<std::endl;
      //std::cout<<theTracker.getX()<<", "<<theTracker.getX2()<<"; "<<theTracker.getY()<<", "<<theTracker.getY2()<<std::endl;
      //std::cout<<theTracker.getRotation()<<" "<<theTracker.getHeading()<<std::endl;
      //std::cout<<Axial.getPosition()<<", "<<Axial.position(degrees)<<"; "<<Lateral.getPosition()<<", "<<Lateral.position(degrees)<<std::endl;
      //std::cout<<Intake.position(degrees)<<std::endl;
      std::cout<<""<<std::endl;
      Controller1.Screen.setCursor(3,1);
      Controller1.Screen.print(theTracker.getX());
      Controller1.Screen.print(", ");
      Controller1.Screen.print(theTracker.getY());
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
      Assistant.intakeStop();
    }
  }

  /*double dist = Distance.objectDistance(vex::distanceUnits::mm);
  if(dist > 65 && dist < 75 && !Hook.value() && Controller1.ButtonL1.pressing()) {*/
  if(clampTime.update(1 - (HookLimit.pressing() && Controller1.ButtonL1.pressing()), 0.005)) {
    clampTime.reset();
    toggleHook();
    triggered = true;
  }
}