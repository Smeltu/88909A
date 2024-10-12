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

void stopIntake() {
  theTracker.intakeStop();
}

void offensive() { //rel to bottom right corner, alliance side is x-axis
  Auton.Init(96,19.25,270);
  prop();
  Auton.DriveStraight(-22);
  hook();//grab goal
  theTracker.intakeFwd();
  Auton.Goto(117,46);//ring
  Auton.DriveStraight(-24);
  Auton.DriveStraight(12,280,100,20,true);
  Hook.set(false);
  prop();
  theTracker.intakeStop();
  Auton.DriveStraight(20,183,80,20,true,__null,prop,13);
  theTracker.intakeFwd();
  Auton.DriveStraight(-5,140);
  wait(400,msec);
  theTracker.intakeStop();
  Auton.DriveStraight(-10,140,100,20,true);
  Auton.DriveStraight(19,180,100,20,true);//14
  Auton.Output(-60,-60);
  wait(200,msec);
  Auton.DriveStraight(-9,90,60,20,true);
  theTracker.intakeFwd();
  wait(1000,msec);
  theTracker.intakeRev();
  /*Auton.DriveStraight(-8,120,60,20,true,__null,stopIntake,6);//-14 to center
  Auton.DriveStraight(-3,170,40,20,true);
  Auton.DriveStraight(7,130,40,20,true);
  Auton.Output(-30,-60);
  wait(500,msec);
  Auton.Output(20,20);
  wait(200,msec);
  Auton.StopMotors();
  theTracker.intakeFwd();
  wait(800,msec);
  Auton.DriveStraight(36,90,60,20,true,__null,stopIntake,15);*/
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,19.25,270);
  prop();
  Auton.DriveStraight(-21, 270);//18.2
  hook();
  vex::task::sleep(100);
  theTracker.intakeFwd();
  Auton.Goto(25,63.5);
  Auton.DriveStraight(-10,160);
  Auton.DriveStraight(13);
  Auton.DriveStraight(-4,90);
  Auton.RotateTo(240);
  Auton.DriveStraight(13);
  Auton.DriveStraight(-4);
  Auton.RotateTo(354);
  Auton.DriveStraight(34);
  //Auton.Output(30,30);
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