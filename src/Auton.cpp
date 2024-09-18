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

void offensive() { //rel to bottom right corner, alliance side is x-axis
  Auton.Init(96,19.75,270);
  Auton.DriveStraight(-12);
  Auton.DriveStraight(-8, 270, 50, 20, false, canHook, hook, 7);//18.2
  hook();
  vex::task::sleep(600);
  theTracker.intakeFwd();
  Auton.Goto(79, 29, 0, true, (Trigger *)__null, (Event)__null, 0, prop, 15);//96,37.5; 90,39 but 99,42
  Prop.set(false);
  vex::task::sleep(400);
  Auton.DriveStraight(-14, 361, 60);
  Auton.DriveStraight(5);
  vex::task::sleep(500);
  Auton.Goto(90, 48, 0, false);
  Auton.RotateTo(135);
  theTracker.intakeFwd();
  Auton.DriveStraight(18);//18.9
  Intake.setPosition(Intake.position(degrees)-0,degrees);
  vex::task::sleep(1000);
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,19.75,270);
  prop();
  Auton.DriveStraight(-12, 270, 60);
  Auton.DriveStraight(-8, 270, 50, 20, false, canHook, hook, 7);//18.2
  hook();
  vex::task::sleep(500);
  theTracker.intakeFwd();
  vex::task::sleep(1000);
  Auton.Goto(28,46);
  vex::task::sleep(300);
  Auton.Goto(45,51,0,false);
  Auton.RotateTo(235);
  theTracker.intakeFwd();
  Auton.DriveStraight(-14.6);//-16.8
  theTracker.intakeFwd();
  vex::task::sleep(200);
  theTracker.intakeFwd();
  vex::task::sleep(200);
  theTracker.intakeFwd();
  vex::task::sleep(200);
  theTracker.intakeFwd();
  Intake.setPosition(Intake.position(degrees)-0,degrees);
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