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
  //std::cout<<ring<<std::endl;
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

int t = 0;
bool timeBreak() { //remember to set t to 0
  t++;
  if(t>200) {
    t = 0;
    return true;
  }
  return false;
}

bool distBreak() {
  return theTracker.getY()>42;//38
}

bool distBreak2() {
  return theTracker.getY()>49;//46.3
}

void doinker() {
  Doinker.set(!Doinker.value());
}

bool distCheck() {
  return theTracker.getY()>50.5;
}

int ah = 10;
bool autoHook() {
  if(HookLimit.pressing()) {
    ah--;
    if(ah==0) {
      Hook.set(true);
    }
  }
  return false;
}

void doinkerClawToggle() {
  DoinkerClaw.set(!DoinkerClaw.value());
}

int ones = 0;
bool quartSec() {
  ones++;
  if(ones>=25) {
    ones = 0;
    return true;
  }
  return false;
}

bool distCheck2() {
  return theTracker.getX() < 43;
}

void doinkerOff() {
  Doinker.set(false);
}

void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(132,19,90);
  Doinker.set(true);
  theTracker.intakeFwd();
  Auton.DriveStraight(100,112,100,100,true,distCheck);
  Auton.DriveStraight(-20,120,100,15,true,distCheck2,stopIntake,6);
  DoinkerClaw.set(true);
  Auton.DriveStraight(2,120,70,15,false,quartSec);
  Auton.DriveStraight(-4,120,70,15,false,quartSec);
  Doinker.set(false);
  
  Auton.DriveStraight(-19,285,50,15,true,autoHook);
  Auton.DriveStraight(-3,361,30,15,false,quartSec);
  hook();
  theTracker.intakeFwd();
  wait(800,msec);
  theTracker.intakeStop();

  hookOff();
  Auton.DriveStraight(5);
  Auton.DriveStraight(-22.5,355,50,15,true,autoHook);//23.5
  Auton.DriveStraight(-2,361,30,15,false,quartSec);
  hook();

  theTracker.intakeFwd();
  Auton.DriveStraight(26,260,100,15,true);
  t = 100;
  Doinker.set(true);
  Auton.DriveStraight(34,340,100,15,true,timeBreak);
  t = 100;
  Auton.DriveStraight(23,90,100,15,true,timeBreak);
  t = 0;
  Auton.DriveStraight(60,153,100,15,true,timeBreak,doinkerOff,10);
  Auton.Output(20,20);
  //Auton.DriveStraight(30,170,100,100,true);

  /*Auton.DriveStraight(6,270,100,15,true);
  Auton.RotateTo(180);
  hookOff();
  Auton.Goto(96,48,0,false,clampDistCheck);
  Auton.DriveStraight(-3,361,40,15,true);
  hook();*/
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,20.5,270);
  theTracker.toggleSort();
  Auton.DriveStraight(-19,270,100,15,false,autoHook);
  hook();
  Auton.Goto(31,61,0.0,true,__null,__null,0,runIntake,0.1);//25,63.5
  theTracker.toggleSort();
  Auton.DriveStraight(-6,180,100,15);
  Auton.DriveStraight(14,90,100,15);
  Auton.DriveStraight(-4.3,90);
  Auton.RotateTo(270);
  Auton.DriveStraight(13);
  Auton.RotateTo(90);
  Auton.DriveStraight(5);
}

void soloAWP() {
    Auton.DriveStraight(24,114,50,10,true,distBreak2,doinker,8);
    Doinker.set(true);
    Auton.DriveStraight(-15,85,80,15,true,__null,doinker,14);
    Doinker.set(false);
    t = 0;
    Auton.DriveStraight(-16,258,60,15,true,timeBreak,hook,15);
    hook();

    theTracker.intakeFwd();
    Auton.DriveStraight(14.6,270);
    prop();
    wait(1500,msec);
    hookOff();

    Auton.DriveStraight(16,150,100,15,true,check);
    Auton.DriveStraight(-10,90,70,15,true,check);
    theTracker.intakeStop();
    Auton.DriveStraight(-24,355,50,15,true,__null,hook,22);
    theTracker.intakeStop();
    hook();
    theTracker.intakeFwd();
    Auton.DriveStraight(20,20,100,15,true);
}

void offensive2() {
  offensive();
}

void defensive2() {
  defensive();
}

void soloAWP2() {
  Auton.Init(10.5,17,90);
  Auton.DriveStraight(48,95,100,15,false,distBreak);//distBreak is the distance
    Auton.DriveStraight(24,154,50,10,true,distBreak2,doinker,8);
    Doinker.set(true);
    Auton.DriveStraight(-12,85,80,15,true,__null,doinker,11);
    Doinker.set(false);
    t = 0;
    Auton.DriveStraight(-23,248,60,15,true,timeBreak,hook,21.5);
    hook();

    theTracker.intakeFwd();
    Auton.DriveStraight(14.6,270);
    prop();
    wait(1500,msec);
    hookOff();

    Auton.DriveStraight(16,150,100,15,true,check);
    Auton.DriveStraight(-10,90,70,15,true,check);
    theTracker.intakeStop();
    Auton.DriveStraight(-24,355,50,15,true,__null,hook,22);
    theTracker.intakeStop();
    hook();
    theTracker.intakeFwd();
    Auton.DriveStraight(20,20,100,15,true);
}

void skills() {
  Auton.Init(72,9.75,90);
  theTracker.toggleSort();
  
  Prop.set(false);
  Auton.DriveStraight(3,361,50,20);
  theTracker.intakeFwd();
  Auton.DriveStraight(-3,361,20,20);//alliance stake
  wait(100,msec);
  theTracker.intakeRev();

  Auton.DriveStraight(4.8,105,100,15,true);//5.8
  theTracker.intakeFwd();
  Auton.DriveStraight(-28,195.1,80,15,true,__null,hook,26);//195.1
  hook();//goal
  Auton.DriveStraight(5.4);

  Auton.DriveStraight(21.5,90,100,15,true);//23
  Auton.DriveStraight(37,37,100,15,true);//37,38
  wait(400,msec);
  Auton.DriveStraight(34.8,102,100,15,true,__null,arm,32);
  Auton.DriveStraight(-28.8,100,100,15,true);//-27.7

  prop();
  Auton.RotateTo(0);
  Auton.Output(80,80);
  wait(600,msec);
  Auton.StopMotors();
  theTracker.scoreArm();
  wait(400,msec);
  prop();
  t = 0;
  Auton.DriveStraight(-3,361,100,15,false,timeBreak);
  theTracker.toggleArm();
  Auton.DriveStraight(-4.5,361,40);
  theTracker.intakeFwd();

  Auton.DriveStraight(29.4,263,80,15,true);//30.5
  t = -50;
  Auton.DriveStraight(27,272,100,15,true,timeBreak);//29
  Auton.DriveStraight(-11,0,100,15,true);
  t = -30;
  Auton.DriveStraight(23,20,80,15,true,timeBreak);
  Auton.RotateTo(110);
  Auton.DriveStraight(-4);
  theTracker.intakeRev();
  Hook.set(false);
  Auton.Output(-100,-100);
  wait(300,msec);
  theTracker.intakeStop();

  Auton.DriveStraight(12,130,100,15,true);
  t = 0;
  Auton.DriveStraight(-4,180,50,15,true,timeBreak);
  prop();
  Auton.Output(-50,-50);
  wait(500,msec);
  Auton.DriveStraight(24-(t==0)*7,180,100,15,true);//24.3
  t = 0;
  Auton.DriveStraight(6,270,100,15,true,timeBreak);
  Auton.Output(50,50);
  wait(800,msec);
  theTracker.set(theTracker.getX(),9.75);
  Auton.DriveStraight(-9.5);//9.8

  Auton.DriveStraight(-46,336,100,15,true);
  t = 0;
  Auton.DriveStraight(-15,38,70,15,true,timeBreak,hook,13);//14,40
  hook();//goal
  prop();
  Auton.DriveStraight(-8,0,100,15,true);

  theTracker.intakeFwd();
  Auton.DriveStraight(17.7,95,100,15,true);
  wait(1800,msec);
  theTracker.intakeStop();
  Auton.DriveStraight(40,50,100,15,true,__null,runIntake,30);
  Auton.DriveStraight(10,220,100,15,true);
  wait(300,msec);
  theTracker.intakeStop();

  Auton.DriveStraight(48,197,100,15,true,__null,runIntake,30);//197
  t = 0;
  Auton.DriveStraight(32.3,271,70,15,true,timeBreak);
  Auton.DriveStraight(-8,185,100,15,true);
  t = 0;
  Auton.DriveStraight(13,170,100,15,true,timeBreak);
  Auton.RotateTo(50);
  wait(500,msec);
  Hook.set(false);
  theTracker.intakeRev();
  Auton.Output(-100,-100);
  wait(600,msec);

  theTracker.intakeFwd();
  Auton.DriveStraight(51.5,77,100,15,true,__null,arm,24);
  Auton.DriveStraight(10.5,145,50,15,true);
  Auton.DriveStraight(5,180,50,15,true);
  wait(1500,msec);
  prop();
  Auton.Output(80,80);
  wait(1400,msec);
  Auton.StopMotors();
  theTracker.scoreArm();
  wait(400,msec);
  prop();
  t = 0;
  Auton.DriveStraight(-3,361,100,15,false,timeBreak);
  theTracker.toggleArm();

  theTracker.toggleSort();

  Auton.DriveStraight(-46,240,100,15,true);
  prop();
  Auton.DriveStraight(50,0,100,15,true);
  t = 0;
  Auton.DriveStraight(50,20,100,15,true,timeBreak);
}

void test() {
  Auton.Init(0,0,0);
  
  LeftDrive.resetPosition();
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
  RightDrive.resetPosition();
  RightDriveMotorA.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorA.stop();
  RightDriveMotorA.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveA: "<<LeftDriveMotorA.position(degrees)<<std::endl;
  std::cout<<"RightDriveA: "<<RightDriveMotorA.position(degrees)<<std::endl;
  
  LeftDrive.resetPosition();
  LeftDriveMotorB.spin(forward,12,vex::voltageUnits::volt);
  RightDrive.resetPosition();
  RightDriveMotorB.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorB.stop();
  RightDriveMotorB.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveB: "<<LeftDriveMotorB.position(degrees)<<std::endl;
  std::cout<<"RightDriveB: "<<RightDriveMotorB.position(degrees)<<std::endl;

  LeftDrive.resetPosition();
  LeftDriveMotorC.spin(forward,12,vex::voltageUnits::volt);
  RightDrive.resetPosition();
  RightDriveMotorC.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorC.stop();
  RightDriveMotorC.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveC: "<<LeftDriveMotorC.position(degrees)<<std::endl;
  std::cout<<"RightDriveC: "<<RightDriveMotorC.position(degrees)<<std::endl;
}