#ifndef __ASSIST__
#define __ASSIST__

#include "vex.h"
#include "SingleLock.h"
#include "constants.h"
#include "PID.h"

class Assist {

  private:
  
  bool m_Mirrored;
  bool forw;
  bool back;
  double counter;
  int colorSort;
  bool stall;
  double averageColor;
  double averageDist;

  int mode;
  int loadDeg;
  PID armPID;

  public: Assist(bool mirrored);

  void Init();
  void Run();
  void RunIntake();
  void RunArm();
  void gestureCheck();

  bool isMirrored() {
    return m_Mirrored;
  }

  void intakeFwd() {
    back = false;
    forw = !forw;
    if(!forw) {
      Intake.stop();
    } else {
      Intake.spin(forward,12,vex::voltageUnits::volt);
    }
  }

  void intakeRev() {
    forw = false;
    back = !back;
    if(!back) {
      Intake.stop();
    } else {
      Intake.spin(reverse,12,vex::voltageUnits::volt);
    }
  }

  void intakeStop() {
    forw = false;
    back = false;
    Intake.stop();
  }

  void toggleSort() {
    if(colorSort == -1) {
      colorSort = 0;
    } else {
      colorSort = -1;
    }
  }

  void scheduleIntakeStop() {
    colorSort = -2;
  }

  void toggleStall() {
    stall = !stall;
  }

  void setCounter(double count) {
    counter = count;
  }

  void toggleArm() {
    Arm.setMaxTorque(100000000000,vex::currentUnits::amp);
    if(mode == 0) {
      armPID.start(loadDeg);
      mode = -1;
    } else {
      armPID.start(-ArmRot.position(degrees));
      intakeStop();
      mode = 0;
    }
  }

  void scoreArm() {
    armPID.start(0);
    Arm.setMaxTorque(100000000000,vex::currentUnits::amp);
    if(fabs(mode) == 1) {
      mode = 2;
    }
  }
};

#endif