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
  return theTracker.getY()>38.2;//38
}
void doinker() {
  Doinker.set(!Doinker.value());
}

void offensive() { //rel to bottom right corner, alliance side is x-axis
  Auton.Init(96,19.25,270);
  
  prop();
  Auton.DriveStraight(-15);
  Auton.DriveStraight(-7,270,100,15,false,__null,hook,6);
  hook();//grab goal
  theTracker.intakeFwd();
  Auton.Goto(122,46);//ring 117



  Auton.DriveStraight(16,325,100,20,true);
  Auton.DriveStraight(10,280,100,20,true);
  Doinker.set(true);
  Auton.Output(50,50);
  wait(400,msec);
  Auton.DriveStraight(10,180,100,15,true);
  Doinker.set(false);

  /*prop();
  Auton.DriveStraight(18.5,183,55,20,true,spam,prop,13.5);//19.4,15.3
  //theTracker.intakeStop();
  //theTracker.intakeFwd();
  Auton.DriveStraight(-9,140,100,20,false,check);
  theTracker.intakeStop();
  theTracker.intakeFwd();
  Auton.DriveStraight(-10,80,100,20,true,check);
  Auton.DriveStraight(11.3,160,100,20,true,check);//12.5
  Auton.DriveStraight(-7.55,94,70,20,true,check);//-5.9
  Auton.Output(-40,-40);
  //set hooks somehow?
  Intake.setPosition(fmod(fmod(Intake.position(degrees),522.68)+525,522.68),degrees);
  std::cout<<"hi "<<Intake.position(degrees)<<std::endl;
  Intake.spinToPosition((Intake.position(degrees)>400)?519:-2,degrees,100,vex::velocityUnits::pct,false);
  wait(1300,msec);
  Auton.DriveStraight(3,90,80,20,false,check);
  theTracker.intakeStop();
  theTracker.intakeFwd();
  t = 50;
  Auton.DriveStraight(-3,90,20,20,true,timeBreak);
  wait(600,msec);
  theTracker.intakeRev();
  Auton.DriveStraight(29,90,60,30,true,__null,runIntake,5);
  theTracker.intakeStop();*/
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(48,19.25,270);
  prop();
  Auton.DriveStraight(-17,270,100,20);
  Auton.DriveStraight(-4.2,270,60,20,false,__null,hook,1);//18.2
  hook();
  vex::task::sleep(100);
  theTracker.intakeFwd();
  Auton.Goto(25,64);//25,63.5
  Auton.DriveStraight(-9.5,180);
  Auton.DriveStraight(13.7,120);
  Auton.DriveStraight(-4.3,90);
  Auton.RotateTo(240);
  Auton.DriveStraight(13);
  Auton.DriveStraight(-4);
  Auton.DriveStraight(27,354,100,20,true);//42,354
  Auton.Output(20,20);
}

void soloAWP() {
  Auton.Init(12,19.25,270);
  Auton.DriveStraight(-28,361,100,50,false,distBreak);
  Auton.RotateTo(0);
  Auton.DriveStraight(-7,0,90,90,true);//5.9
  Auton.DriveStraight(-13,270,100,15,true);
  Auton.DriveStraight(-3,270,50,15,true,__null,hook,2);
  hook();
  theTracker.intakeFwd();

  prop();
  wait(500,msec);
  Auton.DriveStraight(20,247,60,15,true,__null,hookOff,4);
  wait(200,msec);
  theTracker.intakeStop();
  Auton.DriveStraight(-5,361,100,15,true);
  Auton.DriveStraight(-5.2,20,100,15,true);
  Auton.DriveStraight(-8.5,345,60,15,true,__null,hook,7.5);
  theTracker.intakeStop();
  theTracker.intakeFwd();
  prop();
  Auton.DriveStraight(26,226,100,15,true);
  prop();
  wait(500,msec);
  Auton.DriveStraight(-24,361,60);
  Auton.RotateTo(90);
  Auton.DriveStraight(18,361,50,15,false,__null,stopIntake,6);
}

void offensive2() {
  offensive();
}

void defensive2() {
  defensive();
}

void soloAWP2() {
  soloAWP();
  /*Auton.Init(10.5,17,90);
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
    Auton.DriveStraight(20,20,100,15,true);*/
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
  Auton.DriveStraight(-5);

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