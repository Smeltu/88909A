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

void hookOff() {
  Hook.set(false);
}


bool spam() {
  theTracker.setCounter(12);
  return false;
}


bool hasSeen = false;
bool check() {
  spam();
  int color = Optical.hue();
  bool ring = ((autonMode != 3 || autonMode != 4) && color <= 30) || (autonMode == 3 && autonMode == 4  && (color > 180 && color < 240));
  std::cout<<ring<<std::endl;
  if(ring) {
    hasSeen = true;
  } else if(hasSeen) {
    hasSeen = false;
    theTracker.intakeStop();
  }
  return false;
}

void offensive() { //rel to bottom right corner, alliance side is x-axis
  Auton.Init(96,19.25,270);

  prop();
  Auton.DriveStraight(-22);
  hook();//grab goal
  theTracker.intakeFwd();
  Auton.Goto(120,46);//ring 117

  Auton.RotateTo(90);
  Auton.DriveStraight(3,90);
  /*Auton.DriveStraight(-27);
  Auton.DriveStraight(13.5,274,100,20,true,__null,hookOff,6);//12.4
  prop();
  Auton.DriveStraight(19.5,183,60,20,true,spam,prop,15.3);
  theTracker.intakeStop();
  wait(15,msec);
  theTracker.intakeFwd();
  wait(15,msec);
  Auton.DriveStraight(-6,140,100,20,false,check);
  theTracker.intakeStop();
  theTracker.intakeFwd();
  Auton.DriveStraight(-10,80,100,20,true,check);
  Auton.DriveStraight(14.8,160,100,20,true,check);//14.8
  Auton.DriveStraight(-2.1,180,true,20,false,check);//???
  Auton.DriveStraight(-9.55,94,60,20,true,check);//-5.9
  theTracker.intakeStop();
  theTracker.intakeFwd();
  wait(1200,msec);
  theTracker.intakeRev();
  Auton.DriveStraight(29,90,100,20,true);*/
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