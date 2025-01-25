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
  return theTracker.getY()>47.2;//51.3
}


bool distCheck2() {
  check();
  return theTracker.getY() < 40;
}

void doinkerOff() {
  Doinker.set(false);
}


void restartIntake() {
  Assistant.intakeStop();
  Assistant.toggleSort();
  Assistant.toggleSort();
  Assistant.intakeFwd();
}

void toggleArm() {
  Assistant.toggleArm();
}

void armAndScheduleIntake() {
  arm();
  Assistant.scheduleIntakeStop();
}

void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(132,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(100,113.2,100,100,true,distCheck);
  Auton.DriveStraight(-11.5,105,100,15,true);//15
  Auton.DriveStraight(2,105,70,15,false,quartSec);
  
  Assistant.intakeStop();
  Assistant.toggleSort();
  Assistant.toggleSort();

  Doinker.set(false);
  ones = 0;
  Auton.DriveStraight(-7,105,70,15,false,quartSec);
  ones = 0;
  
  Auton.DriveStraight(-20,271.5,100,15,true); //first goal
  Auton.DriveStraight(-8,361,30,15,false);
  Assistant.intakeFwd();
  hook();
  wait(500,msec);
  Assistant.intakeStop();
  hookOff();

  Auton.DriveStraight(6);//3
  Auton.DriveStraight(-27,348,80,15,true);//23.5
  Auton.DriveStraight(-4);
  ones = 0;
  hook();

  Assistant.intakeFwd();
  wait(100,msec);

  t = 0;
  Auton.DriveStraight(30,283,60,15,true,timeBreak,doinker,28);
  Doinker.set(true);
  t = 60;
  Auton.DriveStraight(39,339,60,15,true,timeBreak);
  t = 100;
  Auton.DriveStraight(28,90,70,15,true,timeBreak);
  Auton.DriveStraight(15,160,90,55,true);
  Auton.DriveStraight(-5,180,90,55,true);
  t = 50;
  Auton.DriveStraight(46,159,90,55,true,timeBreak,doinkerOff,20);
  t = 50;
  Auton.Output(40,40);
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  /*Auton.Init(48,20.5,270);
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
  Auton.Output(60,60);*/

  Auton.Init(55.5,16.5,180);
  theTracker.set(55.5,16.5,180);
  Auton.DriveStraight(-20.7,180,70);
  Auton.DriveStraight(5.5,180,50);
  Auton.RotateTo(90);
  Auton.DriveStraight(-6.5,90,60);
  Assistant.intakeFwd();
  wait(500,msec);
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(56,141,100,15,true);
  Auton.DriveStraight(-14,190,70,15,true);
  Auton.DriveStraight(-5);
  hook();

  Assistant.intakeStop();
  Assistant.toggleSort();
  Assistant.toggleSort();

  Assistant.intakeFwd();
  Auton.DriveStraight(8);
  Auton.DriveStraight(17.5,110,100,15,true);
  Auton.DriveStraight(-8,60,100,15,true);
  Auton.DriveStraight(9,120,100,15,true);
  wait(200,msec);
  Auton.DriveStraight(-16);
  Auton.DriveStraight(27,0,100,15,true);
  Auton.Output(20,20);
}

void soloAWP() {
  Auton.DriveStraight(24);
    /*Auton.DriveStraight(24,114,50,10,true,distBreak2,doinker,8);
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
    Auton.DriveStraight(20,20,100,15,true);*/
}

void offensive2() {
  Auton.Init(108,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(100,66.9,100,100,true,distCheck);//66.8
  Auton.DriveStraight(-13,75,100,15,true);//15
  

  Doinker.set(false);

  ones = 0;
  Auton.DriveStraight(-7,75,70,15,false,quartSec);
  ones = 0;
  
  Assistant.intakeStop();
  Assistant.toggleSort();
  Assistant.toggleSort();

  Auton.DriveStraight(-20,271.5,100,15,true); //first goal
  Auton.DriveStraight(-6,361,30,15,false);
  Assistant.intakeFwd();
  hook();
  wait(500,msec);
  Assistant.intakeStop();
  hookOff();

  Auton.DriveStraight(3);//3
  Auton.DriveStraight(-20.8,347,75,15,true);//second goal
  ones = 0;
  hook();

  Assistant.intakeFwd();
  wait(100,msec);

  t = -30;
  Auton.DriveStraight(41,330,100,15,true,timeBreak,doinker,37);
  Doinker.set(true);
  wait(200,msec);
  t = 100;
  Auton.DriveStraight(15.5,287,100,15,true,timeBreak);
  t = 50;
  Auton.DriveStraight(10,200,100,15,true);//9
  t = 50;
  Auton.DriveStraight(-7,220,90,15,true,timeBreak);
  hookOff();
  Hook.set(false);
  Auton.DriveStraight(7,135,100,15,true);
  Auton.DriveStraight(-14,280,100,15,true);
  /*Auton.DriveStraight(26,183,100,15,true,timeBreak);
  t = 50;
  Auton.DriveStraight(27.5,130,50,15,true,timeBreak);
  Auton.DriveStraight(5,60,50,15,true);*/
  t = 50;
}

void defensive2() {
  //defensive();

  Auton.Init(55.5,16.5,0);
  Auton.DriveStraight(-20.7,180,70);
  Auton.DriveStraight(3.5,180,50);
  Auton.RotateTo(90);
  Auton.DriveStraight(-4.7,90,60);
  Assistant.intakeFwd();
  wait(500,msec);
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(57.2,147,100,15,true);
  Auton.DriveStraight(-14.5,190,70,15,true);
  Auton.DriveStraight(-5);
  hook();

  Assistant.intakeStop();
  Assistant.toggleSort();
  Assistant.toggleSort();

  Assistant.intakeFwd();
  Auton.DriveStraight(8);
  Auton.DriveStraight(17.5,110,100,15,true);
  Auton.DriveStraight(-8,60,100,15,true);
  Auton.DriveStraight(9,120,100,15,true);
  wait(200,msec);
  Auton.DriveStraight(-16);
  Auton.DriveStraight(27,0,100,15,true);
  Auton.Output(20,20);
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
  Auton.DriveStraight(-10,195.5,40,15,true);
  hook();//goal

  Auton.DriveStraight(22,90,100,15,true);
  Auton.DriveStraight(37.3,36,100,15,true);//37
  Auton.DriveStraight(36,102,100,15,true,__null,armAndScheduleIntake,25);
  Auton.DriveStraight(-28,100,80,15,true,__null,restartIntake,17);

  Assistant.intakeStop();
  wait(25,msec);
  Assistant.intakeFwd();
  Auton.RotateTo(0);
  Auton.Output(40,40);
  wait(350,msec);
  Assistant.scoreArm();
  wait(500,msec);
  t = 0;
  Auton.DriveStraight(-7,361,70,15,true,__null,toggleArm,2);//4.5
  restartIntake();

  Auton.DriveStraight(29.4,266,90,15,true);
  t = -80;
  wait(150,msec);
  Auton.DriveStraight(28.5,265,50,15,true,timeBreak);
  wait(150,msec);
  Auton.DriveStraight(-6,355,90,15,true);
  t = -30;
  Auton.DriveStraight(16,33,80,15,true,timeBreak);
  Auton.RotateTo(110);
  t = 50;
  Auton.DriveStraight(-9,361,100,15,true,timeBreak);
  Assistant.intakeRev();
  Hook.set(false);
  Assistant.intakeRev();
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
  Auton.DriveStraight(9,270,80,15,true,timeBreak);
  Auton.Output(40,40);
  wait(500,msec);
  theTracker.set(theTracker.getX(),9.75);
  Auton.DriveStraight(-15,270,60,15,true);
  Assistant.intakeFwd();
  t = 0;
  Auton.DriveStraight(36,180,100,15,true,timeBreak);
  t = 0;
  Auton.RotateTo(0);
  t = -50;
  Auton.DriveStraight(-28,0,50,15,true,timeBreak);//14,40
  hook();//goal
  prop();

  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(20.5,89,100,15,true);
  wait(300,msec);
  Assistant.intakeStop();
  restartIntake();
  Assistant.intakeStop();
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(40,45,100,15,true,__null,runIntake,30);
  Auton.DriveStraight(32,225,100,15,true,__null,stopIntake,10);

  Auton.DriveStraight(28,184,100,15,true,__null,restartIntake,2);//197
  t = 0;
  Auton.DriveStraight(36,267,70,15,true,timeBreak);
  wait(300,msec);
  Auton.DriveStraight(-9.5,185,100,15,true);
  t = 0;
  Auton.DriveStraight(17,160,100,15,true,timeBreak);
  Auton.RotateTo(50);
  wait(500,msec);
  hookOff();
  Assistant.intakeRev();
  Auton.Output(-80,-80);
  wait(600,msec);

  Assistant.intakeFwd();
  Auton.DriveStraight(58,78,100,15,true,__null,arm,24);
  t = 50;
  Auton.DriveStraight(9.5,180,50,15,true,timeBreak);
  wait(1000,msec);
  Auton.Output(40,40);
  wait(500,msec);
  Auton.StopMotors();
  Assistant.scoreArm();
  wait(600,msec);
  t = 0;
  Auton.DriveStraight(-8,180,50,15,false,timeBreak);
  Assistant.toggleArm();
  restartIntake();
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(23,75,100,15,true);
  Auton.DriveStraight(-60,198,100,15,true);
  Auton.DriveStraight(-4);
  hook();
  Assistant.intakeFwd();


  Assistant.toggleSort();

  t = 0;
  Auton.DriveStraight(-70,198,100,15,true,timeBreak);
  Auton.DriveStraight(50,182,100,15,true);
  Auton.DriveStraight(70,178,100,15,true);

  /*Auton.DriveStraight(-46,240,100,15,true);
  Auton.DriveStraight(50,10,100,15,true);
  t = 0;
  Auton.DriveStraight(50,20,100,15,true,timeBreak);*/
}

void test() {
  Auton.Init(0,0,0);
  IntakeB.resetPosition();
  IntakeB.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  IntakeB.stop();
  vex::task::sleep(2000);
  std::cout<<"Intake: "<<IntakeB.position(degrees)<<std::endl;
  IntakeB.resetPosition();

  vex::task::sleep(100000);

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