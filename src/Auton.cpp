#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "Auton.h"
#include "RobotController.h"

extern Tracker theTracker;
extern RobotController Auton;
extern Assist Assistant;

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
  Assistant.intakeStop();
}

void runIntake() {
  Assistant.intakeFwd();
}

void hookOff() {
  Hook.set(false);
}


bool spam() {
  Assistant.setCounter(12);
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
    if(hasSeen<-2){Assistant.intakeStop();}//-9
  }
  return false;
}

void arm() {
  Assistant.toggleArm();
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

bool distCheck() {
  check();
  return theTracker.getY()>48.7;//51.3
}


bool distCheck2() {
  check();
  return theTracker.getX() < 45;
}

void doinkerOff() {
  Doinker.set(false);
}

void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(132,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  Auton.DriveStraight(100,111.3,100,100,true,distCheck);
  Auton.DriveStraight(-20,120,100,15,true,distCheck2,stopIntake,3);
  DoinkerClaw.set(true);
  Auton.DriveStraight(2,120,70,15,false,quartSec);
  ones = 0;
  Auton.DriveStraight(-4,120,70,15,false,quartSec);
  ones = 0;
  Doinker.set(false);
  
  Auton.DriveStraight(-19,285,50,15,true,autoHook);
  Auton.DriveStraight(-3,361,30,15,false,quartSec);
  ones = 0;
  hook();
  Assistant.intakeFwd();
  wait(800,msec);
  Assistant.intakeStop();

  hookOff();
  Auton.DriveStraight(5);//3
  Auton.DriveStraight(-18,355,80,15,true,autoHook);//23.5
  Auton.DriveStraight(-5,361,30,15,false);
  ones = 0;
  hook();

  Assistant.intakeFwd();
  wait(100,msec);

  Auton.DriveStraight(32,272,100,15,true,timeBreak);
  t = 100;
  Auton.DriveStraight(40,342,100,15,true,timeBreak,doinker,0.5);
  t = 100;
  Auton.DriveStraight(23,90,100,15,true,timeBreak);
  t = 125;
  Auton.DriveStraight(12,120,100,55,true,timeBreak,doinkerOff,10);
  wait(200,msec);
  Auton.Output(-100,-100);
  wait(1200,msec);
  Assistant.intakeStop();
  Assistant.intakeRev();
  hookOff();
  wait(200,msec);
  Auton.DriveStraight(10);
  Auton.RotateTo(290);
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,20.5,270);
  Auton.DriveStraight(-20,270,100,15,false,autoHook);
  Auton.DriveStraight(-3,270,80,15,true,autoHook);
  hook();
  Auton.DriveStraight(9,150,100,15,true);
  Auton.DriveStraight(24.8,123,100,15,true,__null,runIntake,5);
  Auton.DriveStraight(-8,140,90,15,true);
  t = 150;
  Auton.DriveStraight(3,160,90,15,true,timeBreak);
  Auton.DriveStraight(10.8,100,100,15);
  Auton.DriveStraight(-4.3,90,100,15,true);
  Auton.DriveStraight(19,267,100,15,true,check);
  wait(100,msec);
  Assistant.intakeStop();
  Auton.DriveStraight(46,342,90,15,true,__null,hookOff,30);//54.2
  t = 100;
  Auton.DriveStraight(-16,90,60,15,true,timeBreak);
  Auton.Output(-10,-10);
  wait(50,msec);
  Auton.DriveStraight(1.5,361,30,15,true,__null,runIntake,0.4);
  wait(400,msec);
  Auton.DriveStraight(15.5);
  Auton.DriveStraight(-20,0,100,15,true,autoHook);
  hook();
  t = 160;
  Auton.DriveStraight(30,45,100,90,true,timeBreak);
  Auton.Output(60,60);
}

void soloAWP() {
    Auton.DriveStraight(24,114,50,10,true,distBreak2,doinker,8);
    Doinker.set(true);
    Auton.DriveStraight(-15,85,80,15,true,__null,doinker,14);
    Doinker.set(false);
    t = 0;
    Auton.DriveStraight(-16,258,60,15,true,timeBreak,hook,15);
    hook();

    Assistant.intakeFwd();
    Auton.DriveStraight(14.6,270);
    prop();
    wait(1500,msec);
    hookOff();

    Auton.DriveStraight(16,150,100,15,true,check);
    Auton.DriveStraight(-10,90,70,15,true,check);
    Assistant.intakeStop();
    Auton.DriveStraight(-24,355,50,15,true,__null,hook,22);
    Assistant.intakeStop();
    hook();
    Assistant.intakeFwd();
    Auton.DriveStraight(20,20,100,15,true);
}

void offensive2() {
  //offensive();
  Auton.Init(132,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  Auton.DriveStraight(100,114.8,100,100,true,distCheck);//111.3
  Auton.DriveStraight(-12,120,100,15,true,/*distCheck2*/__null,stopIntake,3);
  DoinkerClaw.set(true);
  Auton.DriveStraight(2,120,70,15,false,quartSec);
  ones = 0;
  Auton.DriveStraight(-4,120,70,15,false,quartSec);
  ones = 0;
  Auton.DriveStraight(2,120,70,15,false,quartSec);
  ones = 0;
  Auton.DriveStraight(-4,120,70,15,false,quartSec);
  ones = 0;
  Doinker.set(false);
  
  Auton.DriveStraight(-28,285,80,15,true,autoHook);
  Auton.DriveStraight(-5,361,30,15,false,quartSec);
  ones = 0;
  hook();
  wait(300,msec);
  Assistant.intakeFwd();
  wait(100,msec);
  if(HookLimit.value() || true) {
    wait(700,msec);
  }
  Assistant.intakeStop();

  hookOff();
  Auton.DriveStraight(10);
  Auton.DriveStraight(-25,355,80,15,true,autoHook);//23.5
  Auton.DriveStraight(-6,361,30,15,false);
  ones = 0;
  hook();

  Assistant.intakeFwd();
  wait(100,msec);

  Auton.DriveStraight(33.3,263,100,15,true,timeBreak);
  t = 100;
  Auton.DriveStraight(41.5,340,100,15,true,timeBreak,doinker,0.5);
  t = 100;
  Auton.DriveStraight(15,90,60,15,true,timeBreak);
  t = 125;
  Auton.DriveStraight(30,150,80,55,true,timeBreak,doinkerOff,10);
  t = 125;
  Auton.DriveStraight(15,153,70,15,true,timeBreak);
  Auton.Output(30,30);
  
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

    Assistant.intakeFwd();
    Auton.DriveStraight(14.6,270);
    prop();
    wait(1500,msec);
    hookOff();

    Auton.DriveStraight(16,150,100,15,true,check);
    Auton.DriveStraight(-10,90,70,15,true,check);
    Assistant.intakeStop();
    Auton.DriveStraight(-24,355,50,15,true,__null,hook,22);
    Assistant.intakeStop();
    hook();
    Assistant.intakeFwd();
    Auton.DriveStraight(20,20,100,15,true);
}

void skills() {
  Auton.Init(72,8.9,90);
  Assistant.toggleSort();

  Assistant.intakeFwd();
  Auton.DriveStraight(1.5,361,15,15);
  wait(100,msec);
  Auton.DriveStraight(8,90,100,15,true);
  Auton.DriveStraight(-13,195,80,15,true);
  Auton.DriveStraight(-7,195.5,40,15,true,autoHook,hook,6);
  hook();//goal

  Auton.DriveStraight(19.5,90,100,15,true);
  Auton.DriveStraight(37,37,100,15,true);
  Auton.DriveStraight(36,102,100,15,true,__null,arm,32);
  Auton.DriveStraight(-28,100,80,15,true);//26.5

  Auton.RotateTo(0);
  Auton.Output(40,40);
  wait(250,msec);
  Assistant.scoreArm();
  wait(300,msec);
  t = 0;
  Auton.DriveStraight(-3,361,100,15,false,timeBreak);
  Assistant.toggleArm();
  Auton.DriveStraight(-3.5,361,40,15,true,__null,runIntake,3);//4.5

  Auton.DriveStraight(29.4,260,90,15,true);
  t = -80;
  wait(150,msec);
  Auton.DriveStraight(28.5,265,50,15,true,timeBreak);
  wait(150,msec);
  Auton.DriveStraight(-5,0,90,15,true);
  t = -30;
  Auton.DriveStraight(19,30,80,15,true,timeBreak);
  Auton.RotateTo(110);
  t = 50;
  Auton.DriveStraight(-9,361,100,15,true,timeBreak);
  Assistant.intakeRev();
  Hook.set(false);
  Auton.Output(-100,-100);
  wait(300,msec);
  Assistant.intakeStop();

  Auton.DriveStraight(12,130,100,15,true);
  t = 0;
  Auton.DriveStraight(-5,180,50,15,true,timeBreak);
  Auton.Output(-40,-40);
  wait(800,msec);
  Auton.DriveStraight(24-(t==0)*7,180,100,15,true);//24.3
  t = 0;
  Auton.DriveStraight(9,270,100,15,true,timeBreak);
  Auton.Output(50,50);
  wait(500,msec);
  theTracker.set(theTracker.getX(),9.75);
  Auton.DriveStraight(-9.5);//9.8

  Auton.DriveStraight(-10);
  Assistant.intakeFwd();
  t = 0;
  Auton.DriveStraight(35,180,100,15,true,timeBreak);
  t = 0;
  Auton.RotateTo(0);
  t = -50;
  Auton.DriveStraight(-28,0,50,15,true,timeBreak);//14,40
  hook();//goal
  prop();

  Auton.DriveStraight(20,84,100,15,true);
  wait(1200,msec);
  Intake.setPosition(fmod(Intake.position(degrees), 48977.0 / 31.0),degrees);
  while(fmod(Intake.position(degrees), 48977.0 / 31.0)<1500) {
    wait(10,msec);
  }
  Assistant.intakeStop();
  Auton.DriveStraight(40,50,100,15,true,__null,runIntake,30);
  Auton.DriveStraight(10,220,100,15,true);
  wait(300,msec);
  Assistant.intakeStop();

  Auton.DriveStraight(48,197,100,15,true,__null,runIntake,30);//197
  t = 0;
  Auton.DriveStraight(36,271,70,15,true,timeBreak);
  wait(300,msec);
  Auton.DriveStraight(-9.5,185,100,15,true);
  t = 0;
  Auton.DriveStraight(16,160,100,15,true,timeBreak);
  Auton.RotateTo(50);
  wait(500,msec);
  Hook.set(false);
  Assistant.intakeRev();
  Auton.Output(-100,-100);
  wait(800,msec);

  Assistant.intakeFwd();
  Auton.DriveStraight(59.5,85,100,15,true,__null,arm,24);
  t = 0;
  Auton.DriveStraight(5,180,50,15,true,timeBreak);
  wait(1500,msec);
  Auton.Output(40,40);
  wait(500,msec);
  Auton.StopMotors();
  Assistant.scoreArm();
  wait(300,msec);
  t = 0;
  Auton.DriveStraight(-3,361,100,15,false,timeBreak);
  Assistant.toggleArm();

  Assistant.toggleSort();

  Auton.DriveStraight(-46,240,100,15,true);
  Auton.DriveStraight(50,10,100,15,true);
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