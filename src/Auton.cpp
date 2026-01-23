#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "Auton.h"
#include "RobotController.h"
#include <chrono>
#include <vector>
#include <algorithm>
#include "MCL.h"

extern Tracker theTracker;
extern MCL theMCL;
extern RobotController Auton;
extern Assist Assistant;

void stopIntake() {
  Assistant.intakeStop();
}

void runIntake() {
  Assistant.intakeFwd();
}

bool distBreak() {
  return theTracker.getY()>42;
}


void restartIntake() {
  Assistant.intakeStop();
  Assistant.toggleSort();
  Assistant.toggleSort();
  Assistant.intakeFwd();
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

void runLoader() {
  Loader.set(!Loader.value());
}

void scoreMid() {
  Assistant.trapdoorMidScore();
}

int x = 0; // set to time * 10 in ms
bool timeLim() {
  x--;
  return x == -1;
}

bool loaderAndTime() {
  if(x == 45) {
    Loader.set(true);
  }
  return timeLim();
}

void forceBreak() {
  x = 0;
}

void wingAndBreak() {
  forceBreak();
  Wing.set(false);
}

void reverseIntake() {
  Assistant.intakeRev();
}

void catchBall() {
  Loader.set(!Loader.value());
  Assistant.intakeStop();
}

void matchLoadMacro() {
  Loader.set(true);
  Auton.Output(45,45);
  wait(500,msec);
  Auton.Output(-10,-10);
  wait(100,msec);
  Auton.Output(21,21); //10,10
  wait(2000,msec);
}

void offensive() {
  Auton.Init(59,24.5,90);
  Wing.set(true);
  Assistant.intakeFwd();
  Auton.DriveStraight(29.5,125,100,15,true,__null,runLoader,6);
  Auton.RotateTo(225);
  runLoader();
  Auton.DriveStraight(-19,225,100,15,true);
  scoreMid();
  Auton.Output(-20,-20);
  wait(800,msec);
  scoreMid();
  wait(300,msec);
  Auton.DriveStraight(53,225,100,15,true,__null,runLoader,30);
  Auton.RotateTo(270);
  Auton.Output(30,30);
  wait(1000,msec);
  runLoader();
  Auton.DriveStraight(-26,270,100,15,true);
  Auton.Output(-30,-30);
  wait(400,msec);
  Assistant.trapdoorScore();
  wait(1600,msec);

  Assistant.trapdoorScore();
  x = 75;
  double heading = 270;
  Auton.DriveStraight(8,heading,50,30,true,timeLim,forceBreak,5.5);
  x = 75;
  Auton.DriveStraight(-5,heading+50,40,30,true,timeLim,forceBreak,1.5);
  x = 75;
  Auton.DriveStraight(-30,heading-40,50,30,true,timeLim,wingAndBreak,3);
  x = 30;
  Auton.DriveStraight(-30,heading-5,60,30,true,timeLim,forceBreak,4);
  Auton.DriveStraight(-20,270,100,15,true);
  LeftDrive.stop(brakeType::hold);
  RightDrive.stop(brakeType::hold);
}

void defensive() { 
  Auton.Init(85,24.5,90);
  Wing.set(true);
  Assistant.intakeFwd();
  Auton.DriveStraight(25.5,55,100,15,true,__null,runLoader,6);
  Auton.Output(-10,-10);
  wait(150,msec);
  Auton.RotateTo(135,__null,runLoader,50);
  Auton.DriveStraight(16,135,100,15,true,__null,reverseIntake,12);
  Auton.Output(20,20);
  wait(500,msec);
  Assistant.intakeFwd();
  Auton.DriveStraight(-54,135,100,15,true,__null,runLoader,30); // run to loader
  Auton.RotateTo(270);
  Auton.Output(30,30);
  wait(1000,msec);
  runLoader();
  Auton.DriveStraight(-26,270,100,15,true);
  Auton.Output(-30,-30);
  wait(400,msec);
  Assistant.trapdoorScore();
  wait(3000,msec); // 1600

  Assistant.trapdoorScore();
  x = 75;
  double heading = 270;
  Auton.DriveStraight(8,heading,50,30,true,timeLim,forceBreak,5.5);
  x = 75;
  Auton.DriveStraight(-5,heading+50,40,30,true,timeLim,forceBreak,1.5);
  x = 75;
  Auton.DriveStraight(-30,heading-40,50,30,true,timeLim,wingAndBreak,3);
  x = 30;
  Auton.DriveStraight(-30,heading-5,60,30,true,timeLim,forceBreak,4);
  Auton.DriveStraight(-20,270,100,15,true);
  LeftDrive.stop(brakeType::hold);
  RightDrive.stop(brakeType::hold);
}

void soloAWP() {
  
}

void offensive2() {
  
}

void defensive2() {
  
}

void soloAWP2() {
  
}

void skills() {
  Auton.Init(64,7,180); //15.375,180);
  runLoader();
  Wing.set(true);
  Assistant.intakeFwd();
  Auton.DriveStraight(-4.5,180,70,15,true);
  x = 180;//150;//120;
  Auton.DriveStraight(50,180,42,42,true,timeLim,runLoader,3);
  x = 50;
  runLoader();
  Auton.DriveStraight(-3.5,180,60,15,true,timeLim);
  x = 100;
  Auton.DriveStraight(50,180,40,40,true,timeLim,runLoader,3);
  Auton.Output(40,40);
  wait(400,msec);
  Auton.Output(25,25);
  wait(600,msec);
  
  x = 50;
  Auton.DriveStraight(-10,180,70,20,true,timeLim);
  Auton.Output(-20,-20);
  wait(400,msec);
  Assistant.intakeStop();
  wait(450,msec);
  theTracker.set(55.5,Distance.objectDistance(inches) + theMCL.getSensorY() + 0.5);
  theMCL.Start();

  // can maybe skip the forwards and backwards sequence
  Loader.set(false);
  Auton.DriveStraight(18.3,120,100,15,true); //8, 140
  Auton.RotateTo(83); //60
  Auton.DriveStraight(20,83,100,15,true);
  Assistant.intakeFwd();
  Auton.DriveStraight(-5, 83, 30, 20, true,__null,catchBall,4);//runLoader
  Auton.DriveStraight(14,83,100,15,true);
  Auton.DriveStraight(-7.6,83,100,15,true);
  Auton.RotateTo(225);
  x = 200;
  Auton.DriveStraight(-22,225,100,15,true,timeLim,forceBreak,21.5);
  Auton.Output(-15,-15);
  wait(500,msec);
  scoreMid();
  wait(2200,msec);
  Loader.set(false);
  Assistant.resetTrapdoor();
  Assistant.trapdoorScore();
  wait(70,msec);
  Auton.DriveStraight(17,225,100,15,true);
  Assistant.resetTrapdoor();

  // how to avoid balls making this get stuck?
  runLoader();
  Assistant.intakeStop();
  Auton.DriveStraight(39.8,227,100,15,true,__null,runIntake,5); // 39.5

  Auton.RotateTo(270);
  matchLoadMacro();
  Auton.DriveStraight(-6,270,100,15,true,__null,runLoader,3);

  // sequence can be sped up significantly
  Assistant.intakeStop();
  Auton.RotateTo(140);
  Auton.DriveStraight(19,140,100,15,true);
  Auton.RotateTo(90);
  std::cout<<theTracker.getRotation()<<std::endl;
  Auton.DriveStraight(65,90,100,15,true);
  std::cout<<theTracker.getRotation()<<std::endl;
  Auton.DriveStraight(15,65,100,15,true);
  wait(100,msec);
  std::cout<<"Pre-MCL set values: " << theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  theMCL.setTrackerToMCL();
  wait(200,msec);
  std::cout<<"Final coords: " << theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  Auton.Goto(24,theTracker.getY());
  Auton.RotateTo(90);

  wait(100,msec); //stabilize
  theMCL.setX(Distance.objectDistance(inches) + theMCL.getSensorY() + 0.5);
  wait(200,msec);
  x = 100;
  Auton.DriveStraight(-13,90-(theMCL.getX(true)-24)*5,50,15,true,timeLim); // correction since the two turns before this seem to offset us; i.e. if x > 24, aim <90 so that driving backwards puts you closer to 24
  Auton.Output(-10,-10);
  Assistant.trapdoorScore();
  wait(2100,msec); //1800
  Assistant.resetTrapdoor();

  Auton.DriveStraight(16,90,100,15,true);
  matchLoadMacro();
  Auton.DriveStraight(-24,90,100,15,true,__null,runLoader,3);

  Assistant.intakeStop();
  Auton.Output(-15,-15);
  wait(300,msec);
  Assistant.trapdoorScore();
  wait(2100,msec);
  theMCL.setTrackerToMCL();
  wait(100,msec);

  Auton.DriveStraight(14,90,80,15,true);
  Auton.RotateTo(180);
  wait(100,msec);
  std::cout<<theTracker.getRotation()<<std::endl;
  Auton.DriveStraight(-94,180,100,15,true);
  std::cout<<theTracker.getRotation()<<std::endl;
  wait(100,msec);
  std::cout<<"Pre-MCL set values: " << theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  theMCL.setTrackerToMCL();
  wait(200,msec);

  Auton.RotateTo(90);
  runLoader();
  Assistant.resetTrapdoor();
  x = 100;
  Auton.DriveStraight(16,90+(theMCL.getX(true)-120)*6,100,15,true,timeLim,forceBreak);
  matchLoadMacro();
  Auton.DriveStraight(-15,90,80,15,true);
  
  Assistant.intakeStop();
  Loader.set(false);
  Auton.RotateTo(300);
  Auton.DriveStraight(20,300,100,15,true);
  Auton.RotateTo(270);
  std::cout<<theTracker.getRotation()<<std::endl;
  Auton.DriveStraight(60,270,100,15,true);
  std::cout<<theTracker.getRotation()<<std::endl;
  Auton.DriveStraight(15,245,100,15,true);
  wait(100,msec);
  std::cout<<"Pre-MCL set values: " << theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  theMCL.setTrackerToMCL();
  wait(200,msec);
  std::cout<<"Final coords: " << theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  Auton.Goto(119.5,theTracker.getY());
  Auton.RotateTo(270);

  wait(100,msec); //stabilize
  theMCL.setX(Distance.objectDistance(inches) + theMCL.getSensorY() + 0.5);
  wait(200,msec);
  x = 100;
  Auton.DriveStraight(-13,270+(theMCL.getX(true)-120)*5,50,15,true,timeLim); // -13,90-(theMCL.getX(true)-24)*5,50,15,true,timeLim
  wait(2100,msec); //1800
  Assistant.resetTrapdoor();
  
  Auton.DriveStraight(16,90,100,15,true);
  matchLoadMacro();
  Auton.DriveStraight(-24,90,100,15,true,__null,runLoader,3);
  
  Assistant.intakeStop();
  Auton.Output(-15,-15);
  wait(300,msec);
  Assistant.trapdoorScore();
  wait(2100,msec);
  theMCL.setTrackerToMCL();
  wait(100,msec);

  Assistant.intakeStop();
  /*Auton.DriveStraight(14,100,80,15,true);
  Auton.RotateTo(200);
  Auton.DriveStraight(10,200,100,15,true);
  Auton.RotateTo(180);
  Auton.DriveStraight(24,180,90,15,true);
  Auton.DriveStraight(-4.5,180,70,15,true);
  x = 180;//150;//120;
  Auton.DriveStraight(50,180,42,42,true,timeLim,runLoader,3);
  */

  std::cout<<"Final coords: " << theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  while(true) {
    wait(1000,msec);
  }
}

void test() {
  while(Inertial.isCalibrating()) {
    wait(50,msec);
  }
  Auton.Init(24,24,90);
  theMCL.Start();
  wait(500,msec);
  Auton.RotateTo(180);
  
  
  /*auto start = std::chrono::high_resolution_clock::now();
  Auton.RotateTo(0);
  Auton.RotateTo(30);
  Auton.RotateTo(90);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << (duration.count()) << " milliseconds" << std::endl;*/

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
  
  /*Auton.Init(0,0,180);
  Auton.DriveStraight(24,361,100,15,false,trackDist);
  wait(500,msec);
  std::cout<<getTrackedDist()<<std::endl;*/

  //Auton.DriveArc(24,24);
  //Auton.RotateTo(90);
  //Auton.DriveArc(24,48);
}