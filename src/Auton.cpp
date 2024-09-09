#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "Auton.h"
#include "RobotController.h"

extern Tracker theTracker;
extern RobotController Auton;

void hook() {
  Hook.set(true);
}

bool canHook() {
  double dist = Distance.objectDistance(mm);
  return (dist > 65 && dist < 75);
}

void prop() {
  Prop.set(!Prop.value());
}

void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(96,19.75,270);
  Auton.DriveStraight(-21, 361, 70, 20, false, canHook, hook, 19.5);//18.2
  hook();
  vex::task::sleep(100);
  theTracker.intakeFwd();
  vex::task::sleep(300);
  Auton.Goto(78, 30, 0, true, (Trigger *)__null, (Event)__null, 0, prop, 15);
  vex::task::sleep(500);
  Auton.DriveStraight(-10);
  Auton.DriveStraight(5);
  vex::task::sleep(500);
  Auton.Goto(102,54);
  Auton.RotateTo(315);
  Auton.DriveStraight(-19.5);
  theTracker.intakeRev();
  vex::task::sleep(1000);
  theTracker.intakeRev();
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,19.75,270);
  prop();
  Auton.DriveStraight(-14.5);//18.2
  Auton.DriveStraight(-6,361,40,20,false,canHook,hook,6.5);
  hook();
  vex::task::sleep(500);
  theTracker.intakeFwd();
  vex::task::sleep(1000);
  Auton.Goto(28,46);
  vex::task::sleep(300);
  Auton.Goto(58,58,0,false);
  theTracker.intakeFwd();
  Auton.DriveStraight(-4);
}

void offensive2() {
  offensive();
}

void defensive2() {
  defensive();
}

void skills() {
  
}

void test() {
  Auton.Init(0,0,0);
  Auton.DriveStraight(72);
  //vex::task::sleep(3000);
  //Auton.RotateTo(90);
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