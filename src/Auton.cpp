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

void runIntake() {
  theTracker.intakeFwd();
}

void hookOff() {
  Hook.set(false);
}


bool spam() {
  theTracker.setCounter(12);
  return false;
}


int hasSeen = 1;
bool check() {
  spam();
  int color = Optical.hue();
  bool ring = ((autonMode != 4 && autonMode != 5 && autonMode != 6) && color <= 30) || ((autonMode == 4 || autonMode == 5 || autonMode == 6)  && (color > 180 && color < 240));
  std::cout<<ring<<std::endl;
  if(ring) {
    hasSeen = 0;
  } else if(hasSeen<1) {
    hasSeen--;
    if(hasSeen<-5){theTracker.intakeStop();}//-9
  }
  return false;
}

void arm() {
  theTracker.toggleArm();
}

void offensive() { //rel to bottom right corner, alliance side is x-axis
  Auton.Init(96,19.25,270);

  prop();
  Auton.DriveStraight(-22);
  hook();//grab goal
  theTracker.intakeFwd();
  Auton.Goto(120,46);//ring 117

  Auton.DriveStraight(-27);
  Auton.DriveStraight(13.5,274,100,20,true,__null,hookOff,6);//12.4
  prop();
  Auton.DriveStraight(19.4,183,60,20,true,spam,prop,15.5);//19.5,15.3
  theTracker.intakeStop();
  theTracker.intakeFwd();
  Auton.DriveStraight(-6,140,100,20,false,check);
  theTracker.intakeStop();
  theTracker.intakeFwd();
  Auton.DriveStraight(-10,80,100,20,true,check);
  Auton.DriveStraight(12.5,160,100,20,true,check);//14.8
  Auton.DriveStraight(-7.55,94,60,20,true,check);//-5.9
  Auton.Output(-50,-50);
  //set hooks somehow?
  Intake.spinToPosition(Intake.position(degrees)-100,degrees,false);
  wait(1000,msec);
  Auton.DriveStraight(3,361,50,20,false);
  theTracker.intakeStop();
  theTracker.intakeFwd();
  Auton.DriveStraight(-3,90,20,20);
  theTracker.intakeRev();
  Auton.DriveStraight(29,90,100,30,true);
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,19.25,270);
  prop();
  Auton.DriveStraight(-21,270,80);//18.2
  hook();
  vex::task::sleep(100);
  theTracker.intakeFwd();
  Auton.Goto(23,64);//25,63.5
  Auton.DriveStraight(-10,180);
  Auton.DriveStraight(13,120);
  Auton.DriveStraight(-4,90);
  Auton.RotateTo(240);
  Auton.DriveStraight(13);
  Auton.DriveStraight(-4);
  Auton.DriveStraight(42,356,100,20,true);//354
  //Auton.Output(30,30);
}

void soloAWP() {
  Auton.Init(48,19.25,270);
  Auton.DriveStraight(-21,270,100,20,false,__null,hook,21);//18.2
  hook();

  vex::task::sleep(100);
  theTracker.intakeFwd();
  Auton.DriveStraight(28,150,100,20,true,check);
  Auton.DriveStraight(28,290,100,20,true,check,hookOff,8);
  theTracker.intakeStop();
  Auton.DriveStraight(30,340,100,20,true);

  Auton.RotateTo(90);
  Auton.DriveStraight(-2,90,30,20,true,__null,runIntake,1);
}

void offensive2() {
  offensive();
}

void defensive2() {
  defensive();
}

void soloAWP2() {
  soloAWP();
}

void skills() {
  Auton.Init(72,9.75,90);
  Prop.set(false);
  Auton.DriveStraight(3,361,50,20);
  theTracker.intakeFwd();
  Auton.DriveStraight(-3,361,20);
  theTracker.intakeRev();
  Auton.DriveStraight(6);
  theTracker.intakeFwd();
  Auton.DriveStraight(-24,198,100,15,true,__null,hook,19);//195
  hook();
  Auton.DriveStraight(23,90,100,15,true);//20
  Auton.DriveStraight(36,40,100,15,true);
  Auton.DriveStraight(34,100,100,15,true,__null,arm,30);
  Auton.DriveStraight(-29,100);

  prop();
  Auton.RotateTo(0);
  Auton.Output(80,80);
  wait(600,msec);
  Auton.StopMotors();
  theTracker.scoreArm();
  wait(1000,msec);
  theTracker.toggleArm();
  prop();
  Auton.DriveStraight(-10);
  theTracker.intakeFwd();
  Auton.DriveStraight(30,255,100,15,true);
}

void test() {
  Auton.Init(0,0,0);
  //Auton.DriveStraight(72);
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