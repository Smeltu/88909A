#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "Auton.h"
#include "RobotController.h"

extern Tracker theTracker;
extern RobotController Auton;

void runIntake(vex::directionType dir) {
  Intake.spin(dir,12,vex::voltageUnits::volt);
}

void defensive() {
  
}

void offensive() {

}

void offensive2() {

}

void defensive2() {

}

void skills() {
  
}

void test() {
  Auton.Init(0,0,0);
  Auton.DriveStraight(24);
  //vex::task::sleep(3000);
  Auton.RotateTo(90);
  /*LeftDrive.resetPosition();
  RightDrive.resetPosition();
  LeftDrive.spin(forward,12,vex::voltageUnits::volt);
  RightDrive.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDrive.stop();
  RightDrive.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDrive: "<<LeftDrive.position(degrees)<<std::endl;
  std::cout<<"RightDrive: "<<RightDrive.position(degrees)<<std::endl;
  LeftDrive.resetPosition();
  LeftDriveMotorA.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorA.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveA: "<<LeftDriveMotorA.position(degrees)<<std::endl;
  LeftDrive.resetPosition();
  LeftDriveMotorB.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorB.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveB: "<<LeftDriveMotorB.position(degrees)<<std::endl;
  LeftDrive.resetPosition();
  LeftDriveMotorC.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorC.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveC: "<<LeftDriveMotorC.position(degrees)<<std::endl;

  RightDrive.resetPosition();
  RightDriveMotorA.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  RightDriveMotorA.stop();
  vex::task::sleep(2000);
  std::cout<<"RightDriveA: "<<RightDriveMotorA.position(degrees)<<std::endl;
  RightDrive.resetPosition();
  RightDriveMotorB.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  RightDriveMotorB.stop();
  vex::task::sleep(2000);
  std::cout<<"RightDriveB: "<<RightDriveMotorB.position(degrees)<<std::endl;
  RightDrive.resetPosition();
  RightDriveMotorC.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  RightDriveMotorC.stop();
  vex::task::sleep(2000);
  std::cout<<"RightDriveC: "<<RightDriveMotorC.position(degrees)<<std::endl;*/
}