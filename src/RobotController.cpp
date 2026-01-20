#include "vex.h"
#include "iostream"
#include "RobotController.h"
#include "constants.h"

using namespace std;
using namespace vex;

//consts
const double Degree2Arc = PI / 180.0;

//driveStraight
PID dsPID = PID(6.7, 1, 0.15, 5);
PID aePID = PID(1.1, 0.22, 0.09, 15);
BreakTimer dsSmall = BreakTimer(0.3, 0.1);
BreakTimer dsLarge = BreakTimer(1.5, 0.5);

//rotateTo
PID rtPID = PID(2.6, 30, 0.07, 10); //2.6, 30, 0.07, 10 -> 2000
BreakTimer rtSmall = BreakTimer(0.5, 0.1);
BreakTimer rtLarge = BreakTimer(1, 0.3);

//driveArc
PID daPID = PID(dsPID.get('p'), dsPID.get('i'), dsPID.get('d')); //move PID - remember it's in inches, not degrees
PID arPID = PID(3.5, 5, 0.175, 10); //rotate PID, also used in anglimit
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
  
  std::cout << "Starting GoTo; Target: " << X << ", " << Y << std::endl;
  
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

  RotateTo(arfa + AngleCalibrate, __null, positionEvent, EventAngle);

  // second step : MoveStraight
  x = m_Tracker.getX();
  y = m_Tracker.getY();
  dx = X - x;
  dy = Y - y;
  delta = sqrt(dx * dx + dy * dy);

  DriveStraight((Forward ? delta : -delta), arfa + AngleCalibrate, 100, 20, false, StopTrigger, StraightMovingEvent, EventDistance);
}

void RobotController::RotateTo(double TargetAngle, Trigger StopTrigger, Event positionEvent /*=NULL*/ , double EventAngle /*= 0*/ ) {
  double angle = m_Tracker.getHeading();
  if (fabs(TargetAngle - angle) < 0.3) { // Don't rotate if less than 0.3 degree
    std::cout << "RotateTo Skipped (Low Error)" << std::endl;
    return;
  }
  
  std::cout << "Starting RotateTo; TargetAngle: " << TargetAngle << ", Current Angle: " << angle << std::endl;
  
  double error = m_Tracker.angleError(TargetAngle);
  double lastError = error;

  rtPID.start(error);

  rtSmall.reset();
  rtLarge.reset();
  
  bool eventHasTriggered = false;

  while (!rtSmall.update(error) && !rtLarge.update(error)) {

    if(fabs(m_Tracker.getHeading() - EventAngle) < 10 && !eventHasTriggered && positionEvent != NULL) {
      positionEvent();
      eventHasTriggered = true;
      std::cout<<"RotatingEvent"<<std::endl;
    }

    error = m_Tracker.angleError(TargetAngle);
    if(error * lastError <= 0) { //reset integral if past target
      rtPID.start(error);
    }

    if(StopTrigger != NULL) {
      if(StopTrigger()) {
        std::cout<<"Stop Trigger; ";
        break;
      }
    }

    double speed = range(rtPID.calculate(error), 10);
    Output(-speed, speed);
    lastError = error;
    vex::task::sleep(10);
  }

  std::cout << "RotateTo done; x: " << m_Tracker.getX() << " y: " << m_Tracker.getY() << " Error: " << m_Tracker.angleError(TargetAngle) << std::endl;
  StopMotors();
}

void RobotController::DriveStraight(double inches, double targetHeading, double maxSpeed, double minSpeed, bool angLimit, Trigger StopTrigger, Event StraightMovingEvent, double EventDistance) {

  //target values
  double targetInches = inches + m_Tracker.getAxial();
  if (targetHeading == 361) {
    targetHeading = m_Tracker.getHeading();
  }

  std::cout << "Starting DriveStraight; Dist: " << inches << ", Heading: " << targetHeading << std::endl;

  //errors
  double headingError = m_Tracker.angleError(targetHeading);
  double error = targetInches - m_Tracker.getAxial();
  double lastError = error;
  dsPID.start(error);
  aePID.start(headingError);
  arPID.start(headingError);

  dsSmall.reset();
  dsLarge.reset();

  double eventDistanceToTarget = fabs(inches) - EventDistance;
  bool eventHasTriggered = (StraightMovingEvent == NULL);

  //while loop until close enough to target
  while (!dsSmall.update(error) && !dsLarge.update(error)) {
    //update errors
    error = targetInches - m_Tracker.getAxial();
    headingError = m_Tracker.angleError(targetHeading);

    //calculate overall
    double out = dsPID.calculate(error);

    //calculate a
    double a = aePID.calculate(headingError);
    a = range(a, 0, maxSpeed);

    //angLimit
    if(angLimit) {
      a = arPID.calculate(headingError);
      a = range(a, 0, maxSpeed);
      out *= pow(cos(fmin(fabs(headingError), 90.0) / 180.0 * PI), 2);
    }

    //call StopTrigger
    if(StopTrigger != NULL) {
      if(StopTrigger()) {
        std::cout<<"Stop Trigger; ";
        break;
      }
    }

    //call StraightMovingEvent
    if(fabs(error) < eventDistanceToTarget && !eventHasTriggered) {
      std::cout<<error<<std::endl;
      StraightMovingEvent();
      eventHasTriggered = true;
      std::cout<<"StraightMovingEvent"<<std::endl;
    }

    out = range(out, minSpeed, maxSpeed);

    //output 
    Output(out - a, out + a);

    //update lastErrors
    lastError = error;

    //wait
    vex::task::sleep(10);
  }

  std::cout <<"driveStraight done; x: " << m_Tracker.getX() << " y: " << m_Tracker.getY() << std::endl;
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
  double headingError = m_Tracker.angleError(targetHeading);

  double error = sqrt(dx*dx+dy*dy) * (Forward * 2 - 1);
  double lastError = error;
  daPID.start(error);
  arPID.start(headingError);
  lePID.start(headingError);

  double eventDistFromEnd = error - EventDistance;

  //while loop until close enough to target
  while (fabs(error) > 0.2) {
    //update errors
    dx = X - m_Tracker.getX();
    dy = Y - m_Tracker.getY();
    error = sqrt(dx*dx+dy*dy) * (Forward * 2 - 1);
    targetHeading = atan2(dy, dx) * 180 / PI + (1 - Forward) * 180;
    targetHeading += (targetHeading < 0) * 360;
    headingError = m_Tracker.angleError(targetHeading);

    //calculate a
    double a = arPID.calculate(headingError);
    /*if(fabs(headingError) < 5) {
      a = lePID.calculate(headingError);
    }*/
    a = range(a, 0, maxSpeed);
    //calculate overall
    double out = daPID.calculate(error);

    if(fabs(headingError) < fmax(6,0.25*error)) {
      DriveStraight(error,targetHeading,maxSpeed,minSpeed,true,StopTrigger,StraightMovingEvent,error-eventDistFromEnd);
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
    RightDrive.spin(right, rightPct * 3 / 25.0, vex::voltageUnits::volt);
  } else {
    RightDrive.spin(right, rightPct * 3 / 25.0, vex::voltageUnits::volt);
    LeftDrive.spin(left, leftPct * 3 / 25.0, vex::voltageUnits::volt);
  }
}

void RobotController::StopMotors() {
  m_LeftDrive.spin(vex::directionType::fwd, 0, vex::voltageUnits::volt);
  m_RightDrive.spin(vex::directionType::fwd, 0, vex::voltageUnits::volt);

  m_LeftDrive.stop(hold);
  m_RightDrive.stop(hold);
}