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

void offensive() {
  Auton.Init(20.75,48,180);
  Auton.DriveStraight(-19.5, 361, 100, 20, false, canHook, hook, 19);//18.2
  hook();
  runIntake(forward);
  vex::task::sleep(500);
  Auton.Goto(31, 66, 0, true, (Trigger *)__null, (Event)__null, 0, prop, 15);
  vex::task::sleep(500);
  Auton.DriveStraight(-10);
  Auton.DriveStraight(5);
  vex::task::sleep(500);
  Auton.Goto(54,42);
  Hook.set(false);
  Auton.RotateTo(225);
  Intake.stop();
  Auton.DriveStraight(-26);
  Intake.spin(reverse,12,vex::voltageUnits::volt);
  Auton.DriveStraight(5);
  Intake.spin(reverse,3,vex::voltageUnits::volt);
}

void offensive2() {

}

void defensive2() {

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