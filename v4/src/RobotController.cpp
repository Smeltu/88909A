#include "vex.h"
#include "iostream"
#include "RobotController.h"
#include "constants.h"

using namespace std;
using namespace vex;

//consts
const double Degree2Arc = PI / 180.0;

//driveStraight
PID dsPID = PID(0.3, 0.02, 0.02);//0.6,0.03,0.03
PID aePID = PID(1.1, 0.22, 0.09);
StallCheck dsSC = StallCheck(0.9, 50);

//rotateTo
PID rtPID = PID(3,0.1,0.1);//2, 0.08, 0.1
StallCheck rtSC = StallCheck(0.95, 30);//0.8,40

//driveArc
PID daPID = PID(dsPID.get('p') / degreesToInches, dsPID.get('i') / degreesToInches, dsPID.get('d') / degreesToInches); //move PID - remember it's in inches, not degrees
PID arPID = PID(rtPID.get('p'),rtPID.get('i'),rtPID.get('d')); //rotate PID
PID lePID = PID(aePID.get('p'),aePID.get('i'),aePID.get('d')); //rotate lowError PID

RobotController::RobotController(motor_group & LeftDrive, motor_group & RightDrive, Tracker & theTracker): m_LeftDrive(LeftDrive), m_RightDrive(RightDrive), m_Tracker(theTracker) {
  task event_routine(EventHandlingRoutine, this, 12);
}

void RobotController::AddEvent(Event evt) {
  SingleLock sl(m_csEvent);
  m_lstEvent.push_back(evt);
}

Event RobotController::GetEvent() {
  SingleLock sl(m_csEvent);

  if (m_lstEvent.empty())
    return NULL;

  Event evt = m_lstEvent.front();
  m_lstEvent.pop_front();
  return evt;
}

int RobotController::EventHandlingRoutine(void * pVoid) {
  RobotController * pThis = (RobotController * ) pVoid;
  while (true) {
    Event evt = pThis -> GetEvent();
    if (evt != NULL) {
      ( * evt)(); // call the event
    } else {
      task::sleep(5); // take a break
    }
  }
  return 0;
}

void RobotController::Goto(double X, double Y, double AngleCalibrate, bool Forward, Trigger StopTrigger, Event positionEvent, double EventAngle, Event StraightMovingEvent, double EventDistance) {
  // first step : rotate
  double x = m_Tracker.getX();
  double y = m_Tracker.getY();
  double a = m_Tracker.getHeading();
  double dx = X - x;
  double dy = Y - y;
  StopMotors();

  double arfa = (fabs(dx) < 1.0e-6 && fabs(dy) > 0.01 ? (dy > 0 ? PI / 2 : -PI / 2) : (dx > 0 ? atan(dy / dx) : atan(dy / dx) + PI)) / Degree2Arc;

  if (!Forward) arfa += 180;
  double delta = arfa < a ? 360 : -360;
  while (fabs(arfa - a) > 180) arfa += delta;

  RotateTo(arfa + AngleCalibrate, positionEvent, EventAngle);

  // second step : MoveStraight
  x = m_Tracker.getX();
  y = m_Tracker.getY();
  dx = X - x;
  dy = Y - y;
  delta = sqrt(dx * dx + dy * dy);
  DriveStraight((Forward ? delta : -delta), arfa + AngleCalibrate, 100, 20, false, StopTrigger, StraightMovingEvent, EventDistance);
}

void RobotController::RotateTo(double TargetAngle, Event positionEvent /*=NULL*/ , double EventAngle /*= 0*/ ) {
  std::cout << "Starting RotateTo; TargetAngle: " << TargetAngle << std::endl;
  double angle = m_Tracker.getHeading();
  if (fabs(TargetAngle - angle) < 0.3) // Don't rotate if less than 0.3 degree
    return;
  double v = 0;
  double error = angleError(TargetAngle);
  double lastError = error;
  int counter = 0;
  int lastUpdate = 0;
  rtPID.start(error);
  int moveCheck = error;
  while (fabs(error) > 0.3) {
    counter++;
    error = angleError(TargetAngle);
    if(counter%100==0) {
      if(fabs(moveCheck-error)<0.4) {
        std::cout<<"no movement ";
        break;
      }
      moveCheck = error;
    }
    if (error != lastError) {
      v = (error - lastError)/(counter - lastUpdate);
      lastUpdate = counter;
    }
    double speed = rtPID.calculate(error);
    /*if(fabs(speed) < 0.05 && fabs(error) < 3) {
      std::cout<<"low output ";
      break;
    }*/
    speed = range(speed, 23);//18
    /*if(rtSC.calculate(speed)) {
      std::cout<<"rtSC"<<std::endl;
      if(fabs(error) > 0.3) {
        dsPID.start(error);
        dsSC.start(); 
      }
      else {
        break;
      }
    }*/
    Output(-speed, speed);
    lastError = error;
    vex::task::sleep(10);
  }
  std::cout << "RotateTo done; x: " << m_Tracker.getX() << " y: " << m_Tracker.getY() << " Error: " << angleError(TargetAngle) << std::endl;
  StopMotors();
}

void RobotController::DriveStraight(double inches, double targetHeading, double maxSpeed, double minSpeed, bool angLimit, Trigger StopTrigger, Event StraightMovingEvent, double EventDistance) {
  std::cout << "Starting DriveStraight; Dist: " << inches << std::endl;

  //target values
  double targetDegrees = inches / degreesToInches + m_Tracker.getAxial();
  if (targetHeading == 361) {
    targetHeading = m_Tracker.getHeading();
  }
  //errors
  double headingError = targetHeading - m_Tracker.getHeading();
  double error = inches / degreesToInches;
  double lastError = error;
  double v = 0;
  double counter = 0;
  double lastUpdate = 0;
  dsPID.start(error);
  dsSC.start();
  aePID.start(headingError);
  //while loop until close enough to target
  while (fabs(error) * degreesToInches > 0.2) {
    counter++;
    //update errors
    error = targetDegrees - m_Tracker.getAxial();
    headingError = angleError(targetHeading);
    if (error != lastError) { //used to smooth out pid since motor doesn't update values that fast (NOT NEEDED ANYMORE?)
      v = (error - lastError) / (counter - lastUpdate);
      lastUpdate = counter;
    }
    else {
      v *= (counter - lastUpdate - 1.0) / (counter - lastUpdate);
    }

    //calculate a
    double a = aePID.calculate(headingError);
    a = range(a, 0, maxSpeed);
    //calculate overall
    double out = dsPID.calculate(error);
    if(fabs(out) < 0.1 && counter > 100 && error < 30 && minSpeed != maxSpeed) {
      std::cout<<"low output ";
      break;
    }
    if(dsSC.calculate(out)) {
      std::cout<<"dsSC"<<std::endl;
      if(fabs(error) * degreesToInches > 0.2) {
        dsPID.start(error);
        dsSC.start(); 
      }
      else {
        break;
      }
    }
    out = range(out, minSpeed, maxSpeed);
    if(minSpeed==maxSpeed && (out * inches <= 0 || error * inches <= 0)) {
      std::cout<<"minMax Break ";
      break;
    }

    //cap speed at start??
    //out = range(out, minSpeed, (RightDrive.velocity(vex::velocityUnits::pct)+LeftDrive.velocity(vex::velocityUnits::pct))/2.0+50);

    //angLimit
    if(angLimit) {
      a = arPID.calculate(headingError);
      a = range(a, 0, maxSpeed);
      out *= pow(cos(fmin(fabs(headingError),90.0) / 180.0 * PI),2);
    }

    //output 
    Output(out - a, out + a);

    //update lastErrors
    lastError = error;

    //wait
    vex::task::sleep(10);
  }
  std::cout << "driveStraight done; x: " << m_Tracker.getX() << " y: " << m_Tracker.getY() << std::endl;
  if(minSpeed == maxSpeed) {Output(minSpeed,minSpeed);return;}
  StopMotors();
}

void RobotController::DriveArc(double X, double Y, bool Forward, double maxSpeed, double minSpeed, Trigger StopTrigger, Event positionEvent, double EventAngle, Event StraightMovingEvent, double EventDistance) {
  std::cout << "Starting DriveArc; Target: " << X << ", " << Y << std::endl;
  double dx = X - m_Tracker.getX();
  double dy = Y - m_Tracker.getY();
  if(dx == 0 && dy == 0) {return;}


  //errors
  double targetHeading = atan2(dy, dx) * 180 / PI + (1 - Forward) * 180;
  targetHeading += (targetHeading < 0) * 360;
  double headingError = angleError(targetHeading);

  double error = sqrt(dx*dx+dy*dy) * (Forward * 2 - 1);
  double lastError = error;
  double counter = 0;
  daPID.start(error);
  arPID.start(headingError);
  lePID.start(headingError);

  //while loop until close enough to target
  while (fabs(error) > 0.2) {
    counter++;
    //update errors
    dx = X - m_Tracker.getX();
    dy = Y - m_Tracker.getY();
    error = sqrt(dx*dx+dy*dy) * (Forward * 2 - 1);
    targetHeading = atan2(dy, dx) * 180 / PI + (1 - Forward) * 180;
    targetHeading += (targetHeading < 0) * 360;
    headingError = angleError(targetHeading);

    //calculate a
    double a = arPID.calculate(headingError);
    if(fabs(headingError) < 8) {
      a = lePID.calculate(headingError);
    }
    a = range(a, 0, maxSpeed);
    //calculate overall
    double out = daPID.calculate(error);


    if(fabs(out) < 1 && counter > 100 && error < 0.5 && minSpeed != maxSpeed) {
      std::cout<<"low output ";
      break;
    }
    else if(minSpeed == maxSpeed && (fabs(headingError) < 10 || fabs(error) < 10)) {
      std::cout<<"minmax; x:"<<m_Tracker.getX()<<", y:"<<m_Tracker.getY()<<"; transition to "<<std::endl;
      DriveStraight(error,targetHeading,maxSpeed,minSpeed);
      break;
    }
    out = range(out, minSpeed, maxSpeed);
    out *= cos(fmin(fabs(headingError),90.0) / 180.0 * PI);
    //output
    Output(out - a, out + a);
    //update lastErrors
    lastError = error;

    //wait
    vex::task::sleep(10);
    //std::cout<<error<<" "<<out<<" "<<targetHeading<<std::endl;
  }
  std::cout << "driveArc done; x: " << m_Tracker.getX() << " y: " << m_Tracker.getY() << std::endl;
  if(minSpeed == maxSpeed) {Output(minSpeed,minSpeed);return;}
  StopMotors();
}

bool leftFirst = true; //alternate running left & right first
void RobotController::Output(double leftPct, double rightPct) {
  //checking if spinning forwards or backwards
  directionType left = vex::forward;
  directionType right = vex::forward;
  if (leftPct < 0) {
    leftPct *= -1;
    left = reverse;
  }
  if (rightPct < 0) {
    rightPct *= -1;
    right = reverse;
  }
  leftFirst = !leftFirst;
  if (leftFirst) {
    LeftDrive.spin(left, leftPct * 3 / 25.0, vex::voltageUnits::volt);
  }
  RightDrive.spin(right, rightPct * 3 / 25.0, vex::voltageUnits::volt);
  if (!leftFirst) {
    LeftDrive.spin(left, leftPct * 3 / 25.0, vex::voltageUnits::volt);
  }
}

void RobotController::StopMotors() {
  m_LeftDrive.spin(vex::directionType::fwd, 0, vex::voltageUnits::volt);
  m_RightDrive.spin(vex::directionType::fwd, 0, vex::voltageUnits::volt);

  m_LeftDrive.stop(hold);
  m_RightDrive.stop(hold);
}