/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       88909A                                                    */
/*    Created:      Mon Mar 13 2023                                           */
/*    Description:  Code for Team 88909A                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//imports
#include "vex.h"
#include "iostream"
#include "DriverController.h"
#include "Auton.h"
#include "main.h"
#include <time.h>
#include "RobotController.h"
#include "constants.h"
#include "Image.h"

using namespace vex;

const int ofs = 1; //goal side
const int def = 2; //ring side
const int solo = 3;//solo
const int ofs2 = 4; //1-3 are red, 4-6 are blue
const int def2 = 5;
const int solo2 = 6;
const int ski = 7;
const int tests = 8;

int autonMode = ofs; // change this for different autons

double setRotation = 0;

//objects
DriverController dc;
 
vex::competition Competition;
Assist Assistant(abs(autonMode-5) <= 1);
Tracker theTracker(LeftDrive, RightDrive, Inertial, Axial, Axial2, Lateral, Assistant.isMirrored());
RobotController Auton(LeftDrive, RightDrive, theTracker);

//autonomous
void auton(void) {
  switch(autonMode) {
    case(def):
      defensive();
      break;
    case(ofs):
      offensive();
      break;
    case(ofs2):
      offensive2();
      break;
    case(def2):
      defensive2();
      break;
    case(solo):
      soloAWP();
      break;
    case(solo2):
      soloAWP2();
      break;
    case(ski):
      skills();
      break;
    case(tests):
      test();
      break;
  }
}

//driverControl
void driverControl(void) {
  dc.Run(Competition);
}

//preAuton
void preAutonomous(void) {
  Axial.setdatarate(10);
  Lateral.setdatarate(10);
  Axial2.setdatarate(10);
  ArmRot.setdatarate(10);
  
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  IntakeA.resetPosition();
  IntakeB.resetPosition();
  IntakeRot.resetPosition();
  Axial.resetPosition();
  Lateral.resetPosition();
  Arm.resetPosition();
  ArmRot.resetPosition();
  Optical.gestureDisable();//Optical.gestureEnable();
  Optical.setLightPower(50);

  Prop.set(true);
  Hook.set(false);
  Endgame.set(false);
  Doinker.set(false);
  DoinkerClaw.set(false);

  Inertial.calibrate();
  while(Inertial.isCalibrating()) {
    vex::task::sleep(10);
  }

  drawLogo();

  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("P-A Done, Prog: ");
  Controller1.Screen.print(autonMode);

  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print("Dt:");
  Controller1.Screen.print((int)(LeftDriveMotorA.temperature(temperatureUnits::celsius)+LeftDriveMotorB.temperature(temperatureUnits::celsius)+LeftDriveMotorC.temperature(temperatureUnits::celsius)+RightDriveMotorA.temperature(temperatureUnits::celsius)+RightDriveMotorB.temperature(temperatureUnits::celsius)+RightDriveMotorC.temperature(temperatureUnits::celsius))/6.0);
  /*Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print(", In:");
  Controller1.Screen.print((int)(IntakeA.temperature(temperatureUnits::celsius)+IntakeB.temperature(temperatureUnits::celsius))/2.0);*/

  Controller1.Screen.setCursor(3,1);

}

//main function
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Competition.autonomous(auton);
  Competition.drivercontrol(driverControl);
  preAutonomous();
  
  while(true) {
    vex::task::sleep(10);
  }
}

