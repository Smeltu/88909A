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
  return theTracker.getY()> 48;//49
}


bool distCheck2() {
  return theTracker.getY() > 38.5;//41
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

void scoreArmAndScheduleIntake() {
  Assistant.scoreArm();
  Assistant.intakeFwd();
  Assistant.scheduleIntakeStop();
}

void armAndScheduleIntake() {
  arm();
  Assistant.scheduleIntakeStop();
}


void setArmToFour() {
  Assistant.setArmMode(700);
}

void setArmDown() {
  Assistant.setArmMode(600);
}

void setArmDown2() {
  Assistant.setArmMode(450);
}

void setArmToZero() {
  Assistant.setArmMode(0);
}

void setArmToZeroAndRestartIntake() {
  setArmToZero();
  restartIntake();
  Assistant.intakeStop();
}

void setArmMid() {
  Assistant.setArmMode(250);
}

void scheduleIntake() {
  Assistant.scheduleIntakeStop();
}


void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(132,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  //Assistant.scheduleIntakeStop();
  //Arm.setPosition(-7,degrees);
  Assistant.toggleArm();
  Assistant.toggleSort();
  Auton.DriveStraight(100,113,100,100,true,distCheck2);//note: distance is not 100 rn, 114
  Auton.DriveStraight(100,99.7,100,100,true,distCheck);//note: distance is not 100 rn, 95
  Auton.DriveStraight(-13,115,100,15,true);//15
  Auton.DriveStraight(4,60,30,15,true,__null,setArmDown,1);
  Auton.Output(-10,-10);
  //Arm.setPosition(Arm.position(degrees)+75,degrees);
  wait(150,msec);
  Assistant.toggleSort();
  Auton.DriveStraight(-10,130,100,15,true,__null,setArmDown2,5);
  setArmDown();
  doinkerOff();
  Auton.DriveStraight(3,150,100,15,true,__null,setArmMid,1.5);
  Assistant.intakeFwd();
  Assistant.scheduleIntakeStop();

  Auton.DriveStraight(-17,340,100,15,true,__null,stopIntake,3);
  setArmToZero();
  Auton.DriveStraight(-16,355,70,15,true,__null,hook,14);
  hook();
  
  ones = -175;
  restartIntake();
  Auton.DriveStraight(30.5,285,100,15,true,quartSec,doinker,29);
  ones = -175;
  Auton.DriveStraight(19,340,80,15,true,quartSec);
  ones = -50;
  Auton.DriveStraight(7.2,340,50,15,true,quartSec,stopIntake,5);
  Auton.DriveStraight(13,115,80,15,true,__null,restartIntake,5);
  Auton.DriveStraight(25,180,100,15,true,__null,doinkerOff,3);
  ones = -125;
  //Assistant.resetAfterAuton();
  Auton.DriveStraight(32,140,50,15,true,quartSec,doinker,15);
  Assistant.intakeStop();
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(84,16.5,270);
  Assistant.toggleArm();
  wait(200,msec);
  restartIntake();
  Assistant.toggleSort();
  wait(700,msec);
  Assistant.setArmMode(600);
  Auton.DriveStraight(4.2,313,100,15,true);
  Auton.Output(-8,-8);
  wait(300,msec);
  Assistant.toggleSort();
  Auton.DriveStraight(-16.5,315,100,15,true,__null,setArmMid,4);
  Auton.DriveStraight(-7,270,90,15,true);
  Auton.DriveStraight(-14,270,50,15,true,__null,hook,11);
  Assistant.intakeFwd();
  Auton.DriveStraight(10,155,100,15,true);//10.8
  ones = -125;
  Auton.DriveStraight(14,179,30,15,true,quartSec);
  wait(200,msec);

  Auton.DriveStraight(-6,169,100,15,true);
  ones = -125;
  Auton.DriveStraight(11,175,30,15,true,quartSec);
  wait(100,msec);
  Auton.DriveStraight(-4.5,158,100,15,true);
  Auton.DriveStraight(19,310,45,15,true);
  Auton.DriveStraight(15,6,100,15,true);
  //Assistant.resetAfterAuton();
  setArmToZero();
  Auton.DriveStraight(20,15,35,15,true,__null,stopIntake,1);
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
  Auton.Init(132,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  Assistant.scheduleIntakeStop();
  Arm.setPosition(-7,degrees);
  Assistant.toggleArm();
  Auton.DriveStraight(100,114,100,100,true,distCheck2);//note: distance is not 100 rn, 114
  Auton.DriveStraight(100,99.7,100,100,true,distCheck,setArmToZeroAndRestartIntake,5);//note: distance is not 100 rn, 95
  Auton.DriveStraight(-13.5,125,100,15,true);////15
  Auton.DriveStraight(4.3,65,70,15,true,__null,setArmDown,2.5);
  Auton.DriveStraight(-1);
  Arm.setPosition(Arm.position(degrees)+75,degrees);
  //wait(300,msec);
  Auton.DriveStraight(-9,130,100,15,true);
  Assistant.setArmMode(250);
  Auton.DriveStraight(4,361,100,15,true,__null,doinkerOff,2);
  Assistant.intakeFwd();
  Assistant.scheduleIntakeStop();
  Auton.DriveStraight(-16,350,100,15,true,__null,stopIntake,3);//344
  Auton.DriveStraight(-14,344,70,15,true,__null,hook,12);
  hook();
  ones = -175;
  Auton.DriveStraight(30.8,280,100,15,true,quartSec,restartIntake,10);
  ones = -175;
  Auton.DriveStraight(19,353,50,15,true,quartSec,doinker,1);
  ones = -125;
  setArmToZero();
  Auton.DriveStraight(9,350,60,15,true,quartSec,stopIntake,2.5);
  Auton.DriveStraight(10,90,80,15,true,__null,restartIntake,5);
  Assistant.resetAfterAuton();
  Auton.DriveStraight(27.5,180,90,15,true,__null,doinkerOff,2);
  ones = -125;
  Auton.DriveStraight(32,140,50,15,true,quartSec,doinker,15);
  Assistant.intakeStop();
}

void defensive2() {
  Auton.Init(84,16.5,270);
  Assistant.toggleArm();
  Assistant.intakeFwd();
  Assistant.toggleSort();
  wait(700,msec);
  Assistant.setArmMode(600);
  Auton.DriveStraight(4,313,100,15,true);
  Auton.Output(-20,-20);
  wait(300,msec);
  Assistant.toggleSort();
  Auton.DriveStraight(-15,305,100,15,true);
  Assistant.setArmMode(0);
  Auton.DriveStraight(-7,270,100,15,true);
  Auton.DriveStraight(-13,270,70,15,true,__null,hook,10);
  Assistant.intakeFwd();
  Auton.DriveStraight(10.3,143,100,15,true);//10.8
  ones = -125;
  Auton.DriveStraight(14.8,181,30,15,true,quartSec);
  wait(200,msec);

  Auton.DriveStraight(-6);
  ones = -125;
  Auton.DriveStraight(13.2,178,30,15,true,quartSec);
  wait(100,msec);
  Auton.DriveStraight(-4.5,158,100,15,true);
  Auton.DriveStraight(21,285,45,15,true);
  Auton.DriveStraight(15,20,100,15,true);
  //Assistant.resetAfterAuton();
  wait(300,msec);
  Assistant.intakeStop();
  Auton.DriveStraight(20,3,35,15,true);
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
  Auton.Init(132,19,90);
  //Assistant.intakeFwd();
  //Assistant.scheduleIntakeStop();
  Arm.setPosition(-7,degrees);
  Assistant.toggleArm();
  setArmDown();

  wait(2000,msec);
  Assistant.setArmMode(0);
  wait(8000,msec);
  /*Auton.DriveStraight(100,112,100,100,true,distCheck2);//note: distance is not 100 rn, 114
  Auton.DriveStraight(100,100,100,100,true,distCheck,setArmToZeroAndRestartIntake,5);//note: distance is not 100 rn, 95
  Auton.DriveStraight(-13,125,100,15,true);//15
  Auton.DriveStraight(5,80,40,15,true,__null,setArmDown,2);
  Arm.setPosition(Arm.position(degrees)+75,degrees);
  wait(300,msec);
  Auton.DriveStraight(-9,130,100,15,true);
  setArmToZero();
  Auton.DriveStraight(4,361,100,15,true,__null,doinkerOff,2);*/
  Assistant.resetAfterAuton();
  /*Auton.Init(0,0,0);
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
  std::cout<<"RightDriveC: "<<RightDriveMotorC.position(degrees)<<std::endl;*/
}