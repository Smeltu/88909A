#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "DriverController.h"
#include "Tracker.h"
#include "RobotController.h"
#include "MCL.h"

using namespace vex;

extern Tracker theTracker;
extern RobotController Auton;
extern Assist Assistant;

extern MCL theMCL;

//for output
int i=0;

//for macro
bool isMacroOn = false;

//callbacks

void intakeForward() {
  Assistant.intakeFwd();
}

void intakeBackward() {
  Assistant.intakeRev();
}

void toggleLoader() {
  Loader.set(!Loader.value());
}

void wingOn() {
  Wing.set(true);
}

void wingOff() {
  if(isMacroOn) {
    return;
  }
  Wing.set(false);
}

void trapdoor() {
  Assistant.trapdoorScore();
}

void trapdoorMid() {
  Assistant.trapdoorMidScore();
}

bool isBPressed() {
  return Controller1.ButtonB.pressing();
}

int t = 0; // set to time * 10 in ms
bool timeLimit() {
  t--;
  return t == -1;
}

bool cancelMacroOrTimeLimit() {
  return isBPressed() || timeLimit();
}

bool breakFuncAndTimedLoader() {
  if(t == 45) {
    Loader.set(true);
  }
  return cancelMacroOrTimeLimit();
}

void forceTimeBreak() {
  t = 0;
}

void wingAndForceBreak() {
  forceTimeBreak();
  Wing.set(false);
}

bool earlyRotateBreak() {
  return (theTracker.getHeading() < 90);
}

void macro() {
  isMacroOn = true;

  double heading = theTracker.getHeading();
  t = 75;
  Auton.DriveStraight(8,heading,50,30,true,cancelMacroOrTimeLimit,forceTimeBreak,5.5);
  t = 75;
  Auton.DriveStraight(-5,heading+50,40,30,true,cancelMacroOrTimeLimit,forceTimeBreak,1.5);
  t = 75;
  Auton.DriveStraight(-30,heading-40,50,30,true,cancelMacroOrTimeLimit,wingAndForceBreak,3);
  t = 30;
  Auton.DriveStraight(-30,heading-5,60,30,true,cancelMacroOrTimeLimit,forceTimeBreak,4);

  isMacroOn = false;
}

/*void toggleColorSort() {
  Assistant.toggleSort();
}

void toggleStallCode() {
  Assistant.toggleStall();
}

void toggleColorSortAndStallCode() {
  toggleColorSort();
  toggleStallCode();
}*/

DriverController::DriverController() {}

//overall run function
void DriverController::Run(vex::competition Competition) {

  Controller1.ButtonR1.pressed(intakeForward);
  Controller1.ButtonR2.pressed(intakeBackward);
  Controller1.ButtonL1.pressed(wingOff);
  Controller1.ButtonL1.released(wingOn);
  Controller1.ButtonL2.pressed(toggleLoader);
  //Controller1.ButtonDown.pressed(toggleColorSortAndStallCode);
  Controller1.ButtonY.pressed(trapdoor);
  Controller1.ButtonRight.pressed(trapdoorMid); // consider adding autoreset
  Controller1.ButtonDown.pressed(macro); // ButtonB is cancel

  theTracker.Start();
  Auton.Init(64,7,180); // used to be 90
  theMCL.Start(); //takes pos from tracker. CURRENTLY NOT USED BY AUTO

  Wing.set(true);

  if(autonMode == 7) {
    while(Inertial.isCalibrating()) {
      wait(50,msec);
    }
    toggleLoader();
    Assistant.intakeFwd();
    Auton.DriveStraight(-4.5,180,70,15,true);
    t = 180;//150;//120;
    Auton.DriveStraight(50,180,42,42,true,timeLimit,toggleLoader,3);
    t = 50;
    toggleLoader();
    Auton.DriveStraight(-3.5,180,60,15,true,timeLimit);
    t = 100;
    Auton.DriveStraight(50,180,40,40,true,timeLimit,toggleLoader,3);
    Auton.Output(67,67);
    wait(500,msec);
    Auton.RotateTo(75,earlyRotateBreak);

    /*Auton.DriveStraight(3,180);
    Auton.RotateTo(90);
    //Loader.set(true);
    Auton.StopMotors();*/
    // skills start macro
  }
  while(true) {
    if(!isMacroOn) {
      RunDriveTrain();
    }
    /*if(i==90) {
      Brain.Screen.clearLine();
    }
    if(i==0) {
      //std::cout<<"rot: "<<Arm.position(degrees)<<std::endl;
      //std::cout<<Optical.hue()<<" "<<Optical.isNearObject()<<" "<<" "<<std::endl;
      //std::cout<<theTracker.getX()<<", "<<theTracker.getY()<<std::endl;
      //std::cout<<Axial.getPosition()<<", "<<Axial.position(degrees)<<"; "<<Lateral.getPosition()<<", "<<Lateral.position(degrees)<<std::endl;
      //std::cout<<IntakeRot.position(degrees)<<std::endl;
      //std::cout<<IntakeA.position(degrees)<<std::endl;
      //std::cout<<theTracker.getRotation()<<std::endl;
      //std::cout<<std::flush;
      //std::cout<<Distance.objectDistance(inches)<<" "<<Distance.value()<<std::endl;
      Controller1.Screen.setCursor(3,1);
      Controller1.Screen.print(theTracker.getX());
      Controller1.Screen.print(", ");
      Controller1.Screen.print(theTracker.getY());
      Controller1.Screen.print(", ");
      Controller1.Screen.print(theTracker.getHeading());
    }*/
    //std::cout<<theTracker.getX()<<", "<<theTracker.getY()<<", "<<theTracker.getHeading()<<"\n";
    if(i%50==0) {
      std::cout<<theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX(true)<<", "<<theMCL.getY(true)<<std::endl;
      //std::cout<<theTracker.getAxial()<<" "<<Distance.objectDistance(inches)<<std::endl; 
    }
    if(i%2==0) {
      //std::cout<<IntakeA.velocity(vex::percentUnits::pct)<<std::endl;
      //std::cout<<Brain.Timer.time(msec)<<", "<<theTracker.getAxial()<<", "<<theTracker.getHeading()<<", "<<Distance.objectDistance(inches)<<std::endl;
    }
    i = (i+1)%100;
    vex::task::sleep(10); 
  }
}

//individual component run functions

void DriverController::RunDriveTrain() {
  //get forward and turn values, multiply by 1.1 to allow for easier maxing
  double forward = fmin(Controller1.Axis3.position(percent) * 1.1, 100);
  double turn = fmin(Controller1.Axis1.position(percent) * 0.8, 100);

  //if values are small enough, do nothing
  if (fabs(forward) < 5 && fabs(turn) < 5) {
    RightDrive.stop(vex::brakeType::coast);
    LeftDrive.stop(vex::brakeType::coast);
  } else {
    RightDrive.spin(vex::forward, 3 * (forward - turn) / 25.0, vex::voltageUnits::volt);
    LeftDrive.spin(vex::forward, 3 * (forward + turn) / 25.0, vex::voltageUnits::volt);
  }
}