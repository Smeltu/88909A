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

//arm
int mode = 0;
double loadDeg = 230;
PID armPID = PID(0.6,0.2,0.06);

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

void toggleArm() {
  Arm.setMaxTorque(100000000000,vex::currentUnits::amp);
  if(mode == 0) {
    armPID.start(loadDeg);
    mode = 1;
  } else {
    mode = 0;
  }
}

void scoreArm() {
  Arm.setMaxTorque(100000000000,vex::currentUnits::amp);
  if(fabs(mode) == 1) {
    mode = 2;
  }
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
  Controller1.ButtonA.pressed(scoreArm);
  Controller1.ButtonB.pressed(toggleArm);

  theTracker.Start();
  Auton.Init(0,0,0);

  while (true) {
    RunDriveTrain();
    RunHook();
    RunArm();
    if(i==0) {
      std::cout<<"rot: "<<ArmRot.position(degrees)<<std::endl;
      //std::cout<<Optical.hue()<<" "<<Optical.isNearObject()<<" "<<counter<<std::endl;
      //std::cout<<theTracker.getX()<<", "<<theTracker.getX2()<<", "<<theTracker.getY()<<", "<<theTracker.getY2()<<std::endl;
      //std::cout<<theTracker.getRotation()<<" "<<theTracker.getHeading()<<std::endl;
      //std::cout<<Axial.position(degrees)<<" "<<Axial2.position(degrees)<<std::endl;
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

void DriverController::RunArm() {
  double target = 950;
  if(mode == 0) {
    target = loadDeg;
  } else if(mode == 1) {
    target = loadDeg;
  }
  if(fabs(ArmRot.position(degrees)) >= 870 && mode == 2) {
    Arm.stop();
    mode = 1;
    target = loadDeg;
  }
  if(fabs(ArmRot.position(degrees)) < loadDeg + 50 && mode == 0) {
    Arm.stop(vex::brakeType::coast);
  } else {
    double error = target - ArmRot.position(degrees);
    double out = armPID.calculate(error,0.005);
    std::cout<<error<<" "<<out<<std::endl;
    out = Auton.range(out, 0, 100) * 3 / 25.0;
    if(out >= 0) {
      Arm.spin(forward,out,vex::voltageUnits::volt);
    } else {
      Arm.spin(reverse,-out,vex::voltageUnits::volt);
    }
  }
}