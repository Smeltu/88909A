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
  Auton.Init(64,15.375,180);
  Assistant.intakeFwd();
  x = 120;
  Auton.DriveStraight(50,180,62,62,true,timeLim);
  wait(400,msec);
  runLoader();//added
  x = 50;
  Auton.DriveStraight(-5,180,20,20,true,timeLim);
  Auton.Output(-15,-15);
  wait(800,msec);
  runLoader();//added
  Assistant.intakeStop();
  wait(400,msec);
  theTracker.set(55.5,theTracker.getY());
  theMCL.setOdomX(55.5);
  theMCL.setOdomY(theTracker.getY()); //TODO: set using distance sensor
  Loader.set(false);
  Auton.DriveStraight(17,120,100,15,true); //8, 140
  Auton.RotateTo(83); //60
  Auton.DriveStraight(20,83,100,15,true);
  Assistant.intakeFwd();
  Auton.DriveStraight(-5, 83, 30, 20, true,__null,catchBall,4);//runLoader
  Auton.DriveStraight(16,83,100,15,true);//,__null,stopIntake,5); //7.5, , , , true, ,stopIntake
  Auton.DriveStraight(-8.5,83,100,15,true);
  //Loader.set(true);
  //Auton.DriveStraight(6,83,70,15,true,__null,stopIntake,3);
  Auton.RotateTo(225);
  x = 100;
  Auton.DriveStraight(-22.5,225,100,15,true,timeLim,forceBreak,21.5);
  scoreMid();
  wait(1800,msec);
  Loader.set(false);
  Assistant.trapdoorScore();
  wait(70,msec);
  Auton.DriveStraight(22,225,100,15,true);
  Auton.RotateTo(90);
  theMCL.Start();
  //std::cout << "mcl running: " << theMCL.Running() << std::endl;
  wait(200,msec); //longer?
  std::cout<<theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  theMCL.setTrackerToMCL();
  theMCL.Stop();
  Auton.RotateTo(228);
  runLoader();
  Auton.DriveStraight(35,228,100,15,true,__null,runIntake,5);
  Auton.RotateTo(270); //Auton.DriveStraight(8,270,70,15,true);
  
  //inconsistent from here
  Auton.Output(100,100);
  wait(300,msec);
  Auton.Output(50,50);
  wait(1500,msec);
  Auton.DriveStraight(-8,270,100,15,true);
  Auton.DriveStraight(-8,135,100,15,true,__null,runLoader,3);
  theMCL.Start(); //Auton.DriveStraight(24,90,100,15,true);
  std::cout<<theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;
  theMCL.setTrackerToMCL();
  theMCL.Stop();

  //basically untested 
  /*Auton.DriveStraight(78,90,100,15,true);
  Auton.DriveStraight(12,45,100,15,true);
  Auton.Output(100,100);
  wait(300,msec);
  Auton.Output(50,50);
  wait(1500,msec);
  Auton.DriveStraight(-8,90,100,15,true);
  Auton.RotateTo(0);
  Assistant.intakeRev;
  x = 120;
  Auton.DriveStraight(50,180,62,62,true,timeLim);
  wait(400,msec);
  x = 50;
  Auton.DriveStraight(-5,180,20,20,true,timeLim);
  Auton.Output(-15,-15);
  wait(800,msec);
  Assistant.intakeStop();
  */
  
  std::cout<<theTracker.getX()<<", "<<theTracker.getY()<<", "<<theMCL.getX()<<", "<<theMCL.getY()<<std::endl;

  while(true) {
    wait(1000,msec);
  }
}

void test() {

  Auton.Init(24,24,90);
  auto start = std::chrono::high_resolution_clock::now();
  Auton.RotateTo(0);
  Auton.RotateTo(30);
  Auton.RotateTo(90);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << (duration.count()) << " milliseconds" << std::endl;

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