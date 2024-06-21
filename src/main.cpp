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

const int ofs = 1;
const int def = 2;
const int def2 = 3;
const int ski = 4;
const int ofs2 = 5;
const int tests = 6;
const int empty = 8;

int autonMode = ofs; // change this for different autons
double iBrightness = 0;

//objects
DriverController dc;
vex::competition Competition;
Tracker theTracker(LeftDrive, RightDrive, Inertial, Axial, Lateral);
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
    case(ski):
      skills();
      break;
    case(tests):
      test();
      break;
    case(empty):
      break;
  }
}

//driverControl
void driverControl(void) {
  dc.Run(Competition);
}

//preAuton
void preAutonomous(void) {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  Slapper.resetPosition();
  Slapper.setTimeout(5,seconds);
  Intake.resetPosition();
  Pto.set(false);
  Wings.set(false);
  Axial.resetPosition();
  Lateral.resetPosition();
  Axial.setdatarate(10);
  Lateral.setdatarate(10);

  Inertial.calibrate();
  while(Inertial.isCalibrating()) {
    vex::task::sleep(10);
  }

  drawLogo();

  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("P-A Done, Prog: ");
  Controller1.Screen.print(autonMode);

  Controller1.Screen.setCursor(2,1);
  Controller1.Screen.print("P-A T: ");
  Controller1.Screen.print((LeftDriveMotorA.temperature(temperatureUnits::celsius)+LeftDriveMotorB.temperature(temperatureUnits::celsius)+LeftDriveMotorC.temperature(temperatureUnits::celsius)+RightDriveMotorA.temperature(temperatureUnits::celsius)+RightDriveMotorB.temperature(temperatureUnits::celsius)+RightDriveMotorC.temperature(temperatureUnits::celsius))/6.0);
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

