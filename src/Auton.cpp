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
  return theTracker.getY()> 48.7;//49
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

void setArmDownAndRev() {
  Assistant.setArmMode(800);
  Assistant.intakeRev();
}

void setArmDown() {
  Assistant.setArmMode(800);
}

void setArmDown2() {
  Assistant.setArmMode(500);
}

void allianceStake() {
  Assistant.setArmMode(500);
}

void setArmToZero() {
  Assistant.setArmMode(0);
}

void setArmToLoad() {
  Assistant.setArmMode(-1);
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
  dists.push_back(Distance.objectDistance(inches) + 11.2842);
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

double wallStakeTimer = -5;
//double maxDist = 0;
bool findWallStake() {
  if(wallStakeTimer++ < 0) {
    return false;
  }
  double dist = Distance.objectDistance(inches);
  std::cout<<dist<<std::endl;
  //maxDist = fmax(maxDist,dist);
  /*if(maxDist - dist > 0.7) {*/
  if(dist < 20) {
    wallStakeTimer = -100;
    //maxDist = 0;
    return true;
  }
  return false;
}

void raiseArmAndRestartScheduleIntake() {
  restartIntake();
  Assistant.setArmMode(130);
  Assistant.scheduleIntakeStop();
}

bool hookCheckAndTimeBreak() {
  return Hook.value() || quartSec();
}

bool xBreak() {
  return theTracker.getX() < 30;
}

void offensive() { //rel to bottom left corner, alliance side is x-axis
  Auton.Init(132,19,90);
  std::cout<<Arm.position(degrees)<<std::endl;
  Arm.resetPosition();
  Doinker.set(true);
  Assistant.intakeFwd();
  Assistant.toggleArm();
  Assistant.toggleSort();
  Auton.DriveStraight(100,112,100,100,true,distCheck2);
  Auton.DriveStraight(100,106,100,100,true,distCheck);
  Auton.DriveStraight(-13,110,100,15,true);//15
  restartIntake();
  doinkerOff();
  Auton.DriveStraight(1.5,110,15,15,true);
  stopIntake();
  //Assistant.toggleSort();
  //Assistant.intakeFwd();
  Auton.DriveStraight(-5.7,110,100,15,true);
  Auton.DriveStraight(10.3,108,100,15,true,__null,setArmDownAndRev,6.5);
  Assistant.intakeStop();
  wait(300,msec);
  setArmMid();
  wait(200,msec);
  Auton.DriveArc(105,47,false,70,20);
  //Auton.DriveStraight(-13.2,348,100,15,true,__null,setArmMid,2);
  //Auton.DriveStraight(-19.2,355,70,15,true,__null,hook,16.8);
  Auton.DriveStraight(-8,355,60,15,true,__null,hook,6);
  hook();
  
  ones = -150;
  restartIntake();
  Auton.DriveStraight(30.8,285,100,15,true,quartSec);/*,doinker,35.8);*/ //36.8
  setArmToZero();
  ones = -175;
  Auton.DriveStraight(24,340,70,15,true,quartSec);//19,350
  ones = -15;
  Auton.DriveStraight(15,345,70,15,true,quartSec);
  Auton.Output(-80,-80);
  wait(180,msec);
  Auton.Output(100,100);
  wait(300,msec);
  Auton.DriveStraight(-15,335,70,15,true,__null,doinker,13);
  ones = -50;
  Auton.DriveStraight(11,335,80,15,true,quartSec);
  ones = -50;
  Auton.DriveStraight(20,90,90,15,true,quartSec,doinkerOff,13);
  doinkerOff();
  Auton.DriveStraight(51,121,80,15,true,__null,stopIntake,5);
  ones = -125;
  //Auton.DriveStraight(40,156,80,15,true,quartSec,stopIntake,20);
}

void defensive() { //rel to bottom left corner, alliance wall is x-axis
  Auton.Init(60,16,270);
  Auton.DriveStraight(3.3,298.5,100,15,true,__null,allianceStake,1);
  wait(80,msec);//300
  while(Arm.velocity(pct)!=0) {
    wait(5,msec);
  }
  setArmMid();
  wait(50,msec);
  Auton.DriveStraight(-22,300,100,15,true);
  ones = -100;
  Auton.DriveStraight(-17,266,70,15,true,hookCheckAndTimeBreak,hook,15.5);
  hook();

  restartIntake();
  setArmToZero();
  Auton.DriveArc(29,59,true,90,20,xBreak);
  wait(100,msec);
  ones = -125;
  Auton.DriveStraight(14.5,182.5,70,15,true,quartSec);
  Auton.DriveStraight(17.5,305,70,15,true);
  ones = -25;
  Auton.DriveStraight(-6,350,100,15,true,quartSec);
  ones = -100;
  Auton.DriveStraight(31,252,100,15,true,quartSec,restartIntake,10);
  for(int i=0;i<3;i++) {
    ones = -30;
    Auton.DriveStraight(9,248,63,63,true,quartSec);
    Auton.Output(-80,-80);
    wait(180,msec);
    Auton.Output(100,100);
    wait(230,msec);//280
    if(i<2){
      ones = -10;
      Auton.DriveStraight(-5.5,248,90,90,true,quartSec);
      wait(350,msec);
    }
  }
  Auton.DriveStraight(-33,200,100,15,true);
  Auton.DriveStraight(30,25,60,15,true,__null,stopIntake,3);
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
  Auton.DriveStraight(100,74,100,100,true,distCheck);
  Auton.DriveStraight(-13,90,100,15,true);//15
  Assistant.toggleSort();

  restartIntake();
  Auton.DriveStraight(1,90,15,15,true);
  stopIntake();
  Auton.DriveStraight(-6.7,90,100,15,true,__null,doinkerOff,0.1);
  Auton.DriveStraight(8,100.5,100,15,true,__null,setArmDown,3.5);
  Assistant.intakeStop();
  wait(200,msec);
  setArmMid();
  wait(300,msec);
  //Auton.DriveArc(105,47,false,70,20);
  Auton.DriveStraight(-19,327,55,15,true,hookCheck,hook,17);
  hook();

  /*Auton.DriveStraight(7,45,100,15,true,__null,setArmMid,3);
  Auton.DriveStraight(-15,0,100,15,true);
  Auton.DriveStraight(-14.5,356,70,15,true,__null,hook,13.5);*/
  setArmToZero();
  Auton.DriveStraight(25,280,100,15,true,__null,runIntake,2);
  ones = -35;
  Auton.DriveStraight(35,344,100,15,true,quartSec);
  ones = -100;
  Auton.DriveStraight(25,337,70,15,true,quartSec);
  Auton.Output(-80,-80);
  wait(220,msec);
  Auton.Output(100,100);
  wait(340,msec);
  Auton.DriveStraight(-13,265,70,15,true,__null,doinker,11);
  ones = -50;
  Auton.DriveStraight(16,310,80,15,true,quartSec);

  Auton.DriveStraight(7.5,275,100,15,true,quartSec);
  Auton.DriveStraight(7,160,100,15,true,quartSec,runIntake,3);
  restartIntake();
  Auton.DriveStraight(8,210,100,15,true,__null,doinkerOff,2);
  Auton.DriveStraight(33,140,80,15,true);
  Auton.Output(20,20);
  //Auton.DriveStraight(30,165,60,15,true,__null,stopIntake,15);

}

void defensive2() {
  Auton.Init(60,16,270);
  Auton.DriveStraight(3.3,298.5,100,15,true,__null,allianceStake,1);
  wait(80,msec);//300
  while(Arm.velocity(pct)!=0) {
    wait(5,msec);
  }
  setArmMid();
  wait(50,msec);
  Auton.DriveStraight(-22,300,100,15,true);
  ones = -100;
  Auton.DriveStraight(-17,266,70,15,true,hookCheckAndTimeBreak,hook,15.5);
  hook();

  restartIntake();
  setArmToZero();
  Auton.DriveArc(28,57.4,true,100,20,xBreak);
  ones = -100;
  Auton.DriveStraight(15,183,80,15,true,quartSec);
  Auton.DriveStraight(17.5,292,70,15,true);
  ones = -25;
  Auton.DriveStraight(-6,350,100,15,true,quartSec);
  ones = -100;
  Auton.DriveStraight(33,252,100,15,true,quartSec,restartIntake,10);
  for(int i=0;i<3;i++) {
    ones = -30;
    Auton.DriveStraight(9,238,60,60,true,quartSec);
    Auton.Output(-80,-80);
    wait(130,msec);
    Auton.Output(100,100);
    wait(200,msec);//280
    if(i<2){
      ones = -10;
      Auton.DriveStraight(-6,238,100,80,true,quartSec);
      wait(350,msec);
    }
  }
  Auton.DriveStraight(-33,200,100,15,true);
  Auton.DriveStraight(30,25,65,15,true,__null,stopIntake,3);
}

void soloAWP2() {
  Auton.Init(10.5,17,90);
  Auton.DriveStraight(15,120,100,15,true);
  Auton.DriveStraight(5,0,100,15,true);
  Auton.DriveStraight(-10,90,100,15,true);
  /*Auton.DriveStraight(48,95,100,15,false,distBreak);//distBreak is the distance
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
    Auton.DriveStraight(20,20,100,15,true);*/
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
  ones = -50;
  Auton.DriveArc(126,116,true,100,20,quartSec,__null,__null);
  Auton.DriveArc(126,116,true,45,20);
  toggleArm();

  Auton.DriveStraight(-41,60,100,15,true,__null,restartIntake,3);
  Auton.DriveStraight(-8,137,35,15,true,findWallStake);
  ones = -75;
  Auton.DriveStraight(12,0,70,10,true,quartSec,raiseArmAndRestartScheduleIntake,2);
  Auton.Output(50,50);
  wait(100,msec);
  Assistant.setArmMode(2);
  Assistant.intakeRev();
  wait(70,msec);
  Assistant.intakeStop();
  Auton.Output(50,50);
  wait(300,msec);
  Auton.Output(-10,-10);
  wait(50,msec);
  Auton.Output(30,30);
  wait(150,msec);
  Auton.Output(-10,-10);
  wait(50,msec);
  Auton.Output(30,30);
  wait(150,msec);

  Auton.DriveStraight(-5,361,100,15,false,__null,setArmToLoad,1);
  wait(300,msec);
  restartIntake();
  ones = 0;
  wait(700,msec);
  Auton.DriveStraight(3,361,100,50,true,quartSec);
  Auton.Output(30,30);
  wait(300,msec);
  Assistant.scoreArm();
  Assistant.intakeRev();
  wait(70,msec);
  Assistant.intakeStop();
  Auton.Output(50,50);
  wait(300,msec);
  Auton.Output(-10,-10);
  wait(50,msec);
  Auton.Output(30,30);
  wait(150,msec);
  Auton.Output(-10,-10);
  wait(50,msec);
  Auton.Output(30,30);
  wait(150,msec);
  setArmMid();
  Auton.DriveStraight(-16.2,0,100,15,false,__null,restartIntake,5);

  Assistant.toggleSort();
  Auton.DriveStraight(50,270,60,15,true,trackDist);
  theTracker.set(144-getTrackedDist(),theTracker.getY());
  ones = 0;
  Auton.DriveStraight(6.5,270,100,15,true,quartSec);
  Auton.DriveStraight(20,55,60,15,true);
  wait(300,msec);
  ones = -50;
  Auton.DriveStraight(-13,130,60,15,true,quartSec);
  hookOff();
  setArmToZero();

  Auton.DriveStraight(35,180,90,15,true,trackDist);
  theTracker.set(theTracker.getX(),getTrackedDist());
  std::cout<<theTracker.getY()<<std::endl;
  Auton.DriveArc(55,20,false,60);
  Auton.DriveStraight(-10,0,80,15,true,hookCheck,hook,8);

  restartIntake();
  Auton.DriveStraight(13,95,100,15,true);
  ones = -25;
  Auton.DriveStraight(10,170,100,100,true,quartSec);
  Auton.DriveStraight(43,103,100,15,true);
  Auton.DriveStraight(29,108,60,15,true,__null,toggleArm,25);

  Auton.DriveStraight(25,295,100,15,true,__null,restartIntake,10);
  Auton.DriveStraight(20,210,60,15,true,findWallStake);
  Auton.DriveStraight(5,180,100,15,true);


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