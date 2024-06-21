#include "vex.h"
#include <iostream>
#include "robot-config.h"
#include "Auton.h"
#include "RobotController.h"

extern Tracker theTracker;
extern RobotController Auton;

void runIntake(vex::directionType dir) {
  Intake.spin(dir,12,vex::voltageUnits::volt);
}

void defensive() {
  Auton.Init(17.5, 15.5, 135);//136.3322
  runIntake(forward);
  Auton.DriveStraight(7.8); 
  
  Auton.DriveStraight(-10, 361, 100, 100);
  Auton.Output(-100,-100);
  wait(150,msec);
  
  Auton.RotateTo(200);
  Auton.RotateTo(300);
  Auton.DriveStraight(10,20,80,80);//21
  Auton.RotateTo(0);
  Auton.Output(25,25);
  for(int i=0;i<500;i++) {
    if(!Distance.installed()) {
      if(theTracker.getX()>61) {
        break;
      }
    } else if(Distance.objectDistance(inches)<=12) {
      break;
    }
    vex::task::sleep(10);
  }
  Auton.StopMotors();
  runIntake(reverse);
  wait(1000,msec);
  Intake.stop();
}

void offensive() {//stop stalling
  Auton.Init(78.5,12,180);
  runIntake(forward);
  Auton.DriveStraight(7);
  wait(200,msec);
  Auton.DriveStraight(-5,180,60,60);
  Auton.DriveStraight(-14,180,100,100);
  Auton.DriveStraight(-10.5,185,95,95);
  Auton.DriveStraight(-10,250,95,95);
  
  Auton.DriveStraight(-19,250,95,95);
  Auton.DriveStraight(-12,220,40,40);
  Auton.DriveStraight(-8,280,90,90,true);
  
  Auton.DriveStraight(-5,230,90,90,true);
  Auton.RotateTo(250);
  //Auton.DriveStraight(-7,270,90,90,true);
  Auton.Output(-100,-100);
  wait(800,msec);
  Auton.DriveStraight(5,280,80,80);
  Auton.RotateTo(70);
  runIntake(reverse);
  Auton.Output(80,100);
  wait(500,msec);
  Intake.stop();

  Auton.DriveStraight(-8,50,95,95);
  runIntake(forward);
  Auton.DriveStraight(32,157,85,85,true);
  Auton.Output(50,50);
  wait(200,msec);
  Auton.DriveStraight(6,40,90,90,true);
  Auton.RotateTo(40);
  runIntake(reverse);
  Auton.StopMotors();
  wait(200,msec);
  //Auton.DriveStraight(6,25,90,90);
  //Auton.DriveStraight(-8.5,90,70,70);
  //Auton.StopMotors();
  runIntake(forward);
  Auton.DriveStraight(15,135,75,75);
  Auton.DriveStraight(15,166,70,70,true);
  
  
  Auton.DriveStraight(-12,170,80,80,true);
  Auton.Output(-100,-100);
  wait(350,msec);
  Auton.StopMotors();
  Auton.DriveStraight(10,180);
  
  
  Auton.RotateTo(0);
  wait(200,msec);
  runIntake(reverse);
  Auton.Output(100,100);
  wait(700,msec);
  Auton.DriveStraight(-20,0,80,80);
  Intake.stop();
  Auton.StopMotors();
}

void offensive2() {
  Auton.Init(78.5,11.25,180);
  Intake.spin(forward,12,vex::voltageUnits::volt);
  Auton.DriveStraight(9);
  Auton.DriveStraight(-30,183,98,98);
  Auton.DriveStraight(-15,220,70,70);
  
  Auton.DriveStraight(-20,230,90,90);
  Intake.stop();
  
  Auton.DriveStraight(5,230,90,90);
  Auton.RotateTo(50);
  Auton.DriveStraight(10,90,93,93);
  Intake.spin(reverse,12,vex::voltageUnits::volt);
  Wings.set(true);
  Auton.DriveStraight(10,90,93,93);
  Auton.Output(100,100);
  wait(200,msec);
  Wings.set(false);
  wait(200,msec);
  Auton.Output(-100,-100);
  wait(160,msec);
  Auton.RotateTo(260);
  Auton.Output(-100,-100);
  wait(450,msec);
  Auton.Output(-30,-30);
  wait(200,msec);
  Auton.Output(100,100);
  wait(160,msec);
  Intake.stop();
  Auton.RotateTo(200);

  Intake.spin(forward,12,vex::voltageUnits::volt);
  Auton.DriveStraight(35,135,90,90);
  Auton.DriveStraight(10,210,70,70);
  Auton.Output(70,70);
  vex::task::sleep(200);
  Auton.Output(-100,-100);
  vex::task::sleep(50);
  Auton.RotateTo(60);
  Intake.spin(reverse,12,vex::voltageUnits::volt);
  Auton.DriveStraight(36,0,90,90);
  Auton.Output(100,100);
  vex::task::sleep(200);
  Intake.stop();
  Auton.DriveStraight(-39.4,70);
  Intake.spin(forward,12,vex::voltageUnits::volt);
  Auton.DriveStraight(18,160,100,60);
  Auton.Output(80,100);
  wait(300,msec);
  Auton.RotateTo(0);
  Wings.set(true);
  Auton.Output(100,100);
  Intake.spin(reverse,12,vex::voltageUnits::volt);
  wait(1200,msec);
  Wings.set(false);
  Auton.DriveStraight(-7);
  Intake.stop();
}

void defensive2() {//notes: try to grab middle, wedge other middle, go back and score alliance, then push alley over
  Auton.Init(36,19.25,90);
  runIntake(forward);
  /*Auton.DriveStraight(38.5,78,100,100);//64.5
  Auton.DriveStraight(9,65,80,80);//64.5
  Auton.DriveStraight(-4,90,60,60);//4*/
  Auton.DriveStraight(27,48,100,100);
  Auton.DriveStraight(29.5,90,97,97);
  Auton.DriveStraight(7,90,70,70,true);
  Auton.Output(-1,-1);
  wait(200,msec);
  Auton.DriveStraight(-12.4,90,80,80);//-11.4

  Auton.DriveStraight(1,0,100,100);
  Wings.set(true);
  Auton.DriveStraight(10,345,100,100,true);
  Auton.Output(100,100);
  wait(300,msec);
  Auton.Output(-100,-100);
  Wings.set(false);
  wait(200,msec);
  Auton.DriveStraight(-10,20,90,90);
  wait(50,msec);
  Auton.DriveStraight(-29,80,90,90,true);
  Auton.Output(-90,-90);
  wait(400,msec);
  Auton.Output(-20,-20);
  wait(500,msec);

  Auton.DriveStraight(24,155,80,80,true);
  
  Auton.DriveStraight(-7,135,80,80,true);
  Auton.DriveStraight(-8,170,90,90);
  
  Auton.DriveStraight(-4,270,60,60,true);
  Auton.DriveStraight(3,330,70,70,true);
  Auton.DriveStraight(8,340,90,90,true);
  runIntake(reverse);
  Auton.DriveStraight(13,350,90,90);
  Auton.DriveStraight(-15,335,90,90);
  Auton.Output(-20,-20);
  wait(1000,msec);
  Auton.StopMotors();
  Intake.stop();
  wait(10000,msec);
}

void skills() {
  Auton.Init(124.25,17.5,225);
  Auton.DriveStraight(-9,290,85,85);
  Auton.Output(-100,-100);
  vex::task::sleep(600);
  Auton.Output(-10,-10);
  wait(200,msec);
  theTracker.set(theTracker.getX(),40.5);
  Slapper.spin(reverse,12,vex::voltageUnits::volt);
  Auton.DriveStraight(6,250,100,100,true);
  Auton.DriveStraight(14,175,70,70);
  Auton.Output(-70,-70);
  wait(160,msec);
  Auton.Output(-30,-60);
  wait(300,msec);
  
  Slapper.resetPosition();
  double x = theTracker.getX();
  double y = theTracker.getY();
  while(fabs(SlapperB.position(degrees))<50*540) {//50*540
    vex::task::sleep(20);
    Auton.Output((theTracker.getHeading()-158.801)*3-5,(158.801-theTracker.getHeading())*3-5);//156.801
  }
  theTracker.set(x,y);
  Auton.StopMotors();
  
  Slapper.stop();
  Auton.DriveStraight(3,361,50,50);
  Auton.RotateTo(45);
  Auton.DriveStraight(-14,60,50,50);
  Auton.DriveStraight(-59,350,80,80);
  
  Auton.DriveStraight(-33.5,350,80,80);
  Auton.DriveStraight(-15,275,70,70);//-16.7
  Auton.Output(-90,-100);
  wait(500,msec);
  Auton.DriveStraight(5.9,270,95,95);
  
  Auton.Output(100,100);
  wait(100,msec);
  Auton.Output(-100,-100);
  wait(700,msec);

  Auton.Output(-70,-70);
  wait(500,msec);
  Auton.StopMotors();
  wait(200,msec);
  theTracker.set(theTracker.getX(),40.5);

  Auton.Output(50,50);
  wait(500,msec);
  Auton.Output(-50,-50);
  wait(150,msec);
  Auton.RotateTo(0);
  Auton.Output(-60,-60);
  wait(500,msec);
  Auton.StopMotors();
  wait(130,msec);
  theTracker.set(8,theTracker.getY());

  Intake.spin(forward,12,vex::voltageUnits::volt);
  Auton.DriveStraight(20,350,80,80);
  Auton.DriveArc(54.5,48,70,70);
  Auton.RotateTo(120);
  Wings.set(true);
  //Auton.DriveStraight(4,110,90,90);
  Auton.DriveStraight(18,160,70,70);
  Intake.spin(reverse,12,vex::voltageUnits::volt);
  Auton.Output(100,100);
  wait(600,msec);
  Auton.DriveStraight(-15,180,100,100);
  Auton.Output(50,50);
  wait(200,msec);
  Auton.Output(100,100);
  wait(350,msec);
  Wings.set(false);
  wait(200,msec);
  Intake.stop();

  Auton.DriveStraight(-22,130,93,93);
  Auton.RotateTo(270);
  Auton.DriveStraight(-29,270,90,90);
  Auton.RotateTo(35);
  
  Auton.DriveStraight(-10,0,90,90);
  Auton.Output(-100,-100);
  wait(600,msec);
  Auton.DriveStraight(14,270,90,90);
  
  Auton.DriveStraight(5,270,90,90,false);

  Auton.RotateTo(0);
  
  
  Auton.Output(-100,-100);
  wait(600,msec);
  Auton.DriveStraight(16,270,90,90);
  
  
  

  Auton.RotateTo(270);
  Auton.DriveStraight(-20,270,80,80);
  Auton.DriveStraight(-30,315,80,80);
  
  Auton.DriveStraight(-18,15,80,80);
  Auton.DriveStraight(-20,90,80,80);
  Auton.Output(-100,-100);
  wait(400,msec);
  Auton.DriveStraight(7,90,90,90);
  Auton.Output(-100,-100);
  wait(600,msec);
  Auton.DriveStraight(5);
  

  Auton.StopMotors();
}

void test() {
  Auton.Init(0,0,0);
  LeftDrive.resetPosition();
  LeftDrive.spin(forward,12,vex::voltageUnits::volt);
  vex::task::sleep(10000);
  Brain.Screen.print(LeftDrive.position(degrees));
  vex::task::sleep(100);
  LeftDrive.stop();
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