#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "Auton.h"
#include "RobotController.h"
#include <chrono>
#include <vector>
#include <algorithm>

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
  return theTracker.getY()> 49;
}


bool distCheck2() {
  return theTracker.getY() > 36.5;
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
  Assistant.setArmMode(800);
}

void setArmDown2() {
  Assistant.setArmMode(500);
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

std::vector<double> dists;
bool trackDist() {
  dists.push_back(Distance.objectDistance(inches) - 1.83);
  return false;
}

double getTrackedDist() {
  sort(dists.begin(),dists.end());
  int startIndex = (dists.size() - 1) / 4;
  int endIndex = (3 * dists.size()) / 4;

  double sum = std::accumulate(dists.begin() + startIndex, dists.begin() + endIndex, 0.0);
  double count = endIndex - startIndex;
  dists.clear();
  if(count == 0) {
    return -1;
  }
  return sum / count;
}

void scheduleTwo() {
  Assistant.scheduleIntakeStop();
  Assistant.scheduleIntakeStop();
}

bool hookCheck() {
  return Hook.value();
}

void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(132,19,90);
  Doinker.set(true);
  Assistant.intakeFwd();
  Assistant.toggleArm();
  Assistant.toggleSort();
  Auton.DriveStraight(100,113,100,100,true,distCheck2);
  Auton.DriveStraight(100,100,100,100,true,distCheck);
  Auton.DriveStraight(-13,110,100,15,true);//15

  Assistant.intakeStop();
  Auton.DriveStraight(2.5,110,15,15,true,__null,doinkerOff,1.5);
  Assistant.toggleSort();
  Assistant.intakeFwd();
  Auton.DriveStraight(-6,110,100,15,true);
  Auton.DriveStraight(11,94,100,15,true,__null,setArmDown,6);
  Assistant.intakeStop();
  wait(500,msec);

  Auton.DriveStraight(-13.2,355,100,15,true,__null,setArmMid,2);
  Auton.DriveStraight(-19.2,355,70,15,true,__null,hook,16.8);
  hook();
  
  ones = -150;
  restartIntake();
  Auton.DriveStraight(36.8,285,100,15,true,quartSec,doinker,35.8);
  setArmToZero();
  ones = -175;
  Auton.DriveStraight(19,350,70,15,true,quartSec);
  ones = -50;
  Auton.DriveStraight(9.5,345,60,15,true,quartSec);
  Auton.DriveStraight(15.6,115,80,15,true);
  Auton.DriveStraight(12,185,100,15,true,__null,doinkerOff,3.6);
  ones = -125;
  Auton.DriveStraight(40,156,40,15,true,quartSec,stopIntake,20);
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(84,16.5,270);
  Assistant.toggleArm();
  Auton.DriveStraight(4.6);
  restartIntake();
  Assistant.toggleSort();
  Auton.RotateTo(317);
  Assistant.setArmMode(600);
  wait(450,msec);
  Assistant.toggleSort();
  Auton.DriveStraight(-8.2,309,100,15,true,__null,setArmMid,2);
  Auton.RotateTo(45,doinker,15);
  Auton.RotateTo(100,doinkerOff,85);
  //Auton.DriveStraight(-5,120,70,15,true,__null,doinkerOff,3);
  Auton.DriveStraight(-12,320,100,15,true);
  ones = -175;
  Auton.DriveStraight(-25,263,40,15,true,quartSec,hook,22.5);

  restartIntake();
  setArmToZero();
  Auton.DriveStraight(12.5,151,100,15,true);//15.1
  ones = -125;
  Auton.DriveStraight(17.5,178,60,15,true,quartSec);

  Auton.DriveStraight(-5,165,100,15,true);
  Auton.DriveStraight(19,292,40,15,true);
  Auton.DriveStraight(-10,270,100,15,true);
  Auton.DriveStraight(35,332,100,15,true);
  wait(100,msec);
  Auton.DriveStraight(20,50,60,15,true,__null,stopIntake,3);
  //Auton.DriveStraight(50,0,100,15,true,__null,stopIntake,20);
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
  Assistant.toggleArm();
  Assistant.toggleSort();
  Auton.DriveStraight(100,67,100,100,true,distCheck2);
  Auton.DriveStraight(100,80,100,100,true,distCheck);
  Auton.DriveStraight(-13,90,100,15,true);//15

  Assistant.intakeStop();
  Auton.DriveStraight(2.5,90,15,15,true,__null,doinkerOff,1);
  Assistant.toggleSort();
  Assistant.intakeFwd();
  Auton.DriveStraight(-6,90,100,15,true);
  Auton.DriveStraight(9,102.5,100,15,true,__null,setArmDown,6);//10
  Assistant.intakeStop();
  wait(500,msec);

  Auton.DriveStraight(7,45,100,15,true,__null,setArmMid,3);
  Auton.DriveStraight(-15,0,100,15,true);
  Auton.DriveStraight(-14.5,356,70,15,true,__null,hook,13.5);
  setArmToZero();
  Auton.DriveStraight(22.5,290,100,15,true,__null,runIntake,2);
  ones = -125;
  Auton.DriveStraight(37,17,100,15,true,quartSec);
  doinker();
  Auton.DriveStraight(9,280,40,15,true);
  stopIntake();
  ones = -25;
  Auton.DriveStraight(7.5,275,100,15,true,quartSec);
  Auton.DriveStraight(7,160,100,15,true,quartSec,runIntake,3);
  restartIntake();
  Auton.DriveStraight(8,210,100,15,true,__null,doinkerOff,2);
  Auton.DriveStraight(30,140,100,15,true,__null);
  //Auton.DriveStraight(30,165,60,15,true,__null,stopIntake,15);
  Auton.DriveStraight(15,310,100,15,true,__null,hookOff,5);
  Auton.DriveStraight(-9,255,75,15,true);

}

void defensive2() {
  Auton.Init(84,16.5,270);
  Assistant.toggleArm();
  wait(200,msec);
  restartIntake();
  Assistant.toggleSort();
  wait(750,msec);
  Assistant.setArmMode(600);
  Auton.DriveStraight(4.1,311,75,15,true);//4.3
  wait(350,msec); 
  Assistant.toggleSort();
  Auton.DriveStraight(-11.4,312,100,15,true,__null,setArmMid,2.4);
  Auton.DriveStraight(2.4,350,100,15,true,__null,doinker,1.2);
  wait(200,msec);
  Auton.DriveStraight(-4.8,55,100,15,true,__null,doinkerOff,2.4);
  wait(300,msec);
  Auton.DriveStraight(-13.2,310,100,15,true);
  Auton.DriveStraight(-26,264,70,15,true,__null,hook,23.5);

  Assistant.intakeFwd();
  setArmToZero();
  Auton.DriveStraight(18.3,150,90,15,true);

  Auton.DriveStraight(9.1,182,40,15,true);
  auto start = std::chrono::high_resolution_clock::now();
  ones = -125;
  Auton.DriveStraight(15,195,50,15,true,quartSec);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  bool jammed = duration.count() > 1450; //failsafe
  std::cout<<"jammed: "<<jammed<<std::endl;

  Auton.DriveStraight(-4.5 + jammed,153 - jammed * 3,100,15,true);
  Auton.DriveStraight(17,313,100,15,true);
  //Auton.DriveStraight(-7,280,100,15,true);
  Auton.DriveStraight(20 + jammed * 1.5,3,100,15,true);
  Auton.DriveStraight(19.5,322 - jammed * 15,100,15,true);
  ones = 0;
  Auton.DriveStraight(50,0,100,15,true,__null,stopIntake,20);
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
  Auton.Init(72,9.75,90);
  Assistant.intakeFwd();
  Assistant.toggleSort();
  Auton.DriveStraight(1);
  Auton.DriveStraight(8);
  Auton.DriveArc(84,24,false);
  Auton.DriveStraight(-5,361,100,15,true,hookCheck,hook,3);
  Auton.DriveArc(92,44);
  ones = 5;
  Auton.DriveStraight(7,50,100,100,true,quartSec);
  Auton.DriveArc(128,118,true,80,20,__null,__null,__null,scheduleTwo,20);
  Auton.DriveStraight(-30,45,100,15,true,__null,toggleArm,2);
  Auton.DriveStraight(18.3,272,100,15,true,__null,restartIntake,2);
  restartIntake();
  Auton.DriveStraight(17,0,100,15,true,__null,stopIntake,15);
  Auton.Output(20,20);
  Assistant.scoreArm();
  wait(500,msec);
  Auton.DriveStraight(-4);
  restartIntake();
  Auton.DriveStraight(3);
  wait(400,msec);
  Auton.Output(20,20);
  Assistant.scoreArm();

  while(true) {
    wait(1000,msec);
  }
  /*Auton.Init(72,8.9,90);
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

  /*auto start = std::chrono::high_resolution_clock::now();

  Auton.DriveStraight(24);
  wait(500,msec);
  Auton.DriveStraight(-24);
  wait(500,msec);
  Auton.DriveStraight(5);
  wait(500,msec);
  Auton.DriveStraight(-5);

  Auton.RotateTo(0);
  //wait(500,msec);
  Auton.RotateTo(90);
  //wait(500,msec);
  Auton.RotateTo(75);
  //wait(500,msec);
  Auton.RotateTo(90);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Average: " << (duration.count() - 1500) / 4.0 << " milliseconds" << std::endl;*/

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
  std::cout<<"RightDriveB: "<<RightDriveMotorB.position(degrees)<<std::endl;*/

  /*LeftDrive.resetPosition();
  LeftDriveMotorC.spin(forward,12,vex::voltageUnits::volt);
  RightDrive.resetPosition();
  RightDriveMotorC.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(2000);
  LeftDriveMotorC.stop();
  RightDriveMotorC.stop();
  vex::task::sleep(2000);
  std::cout<<"LeftDriveC: "<<LeftDriveMotorC.position(degrees)<<std::endl;
  std::cout<<"RightDriveC: "<<RightDriveMotorC.position(degrees)<<std::endl; */
  Auton.Init(0,0,180);
  Auton.DriveStraight(24,361,100,15,false,trackDist);
  wait(500,msec);
  std::cout<<getTrackedDist()<<std::endl;
  //Auton.DriveArc(24,24);
  //Auton.RotateTo(90);
  //Auton.DriveArc(24,48);
}