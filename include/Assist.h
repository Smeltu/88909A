#ifndef __ASSIST__
#define __ASSIST__

#include "vex.h"
#include "SingleLock.h"
#include "constants.h"
#include "PID.h"
#include "BreakTimer.h"

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
  int intakeMode;

  public: Assist(bool mirrored);

  void Init();
  void Run();
  void RunIntake();
  void RunArm();
  void gestureCheck();
  void scheduleCheck();
  void resetAfterAuton();

  bool isMirrored() {
    return m_Mirrored;
  }

  void setMode(int mode) {
    intakeMode = mode;
  }

  void intakeFwd() {
    back = false;
    forw = !forw;
    if(!forw) {
      intakeStop();
    } else {
      IntakeA.spin(forward,12,vex::voltageUnits::volt);
      IntakeB.spin(forward,12,vex::voltageUnits::volt);
    }
  }

  void intakeRev() {
    forw = false;
    back = !back;
    if(!back) {
      intakeStop();
    } else {
      IntakeA.spin(reverse,12,vex::voltageUnits::volt);
    }
  }

  void intakeStop() {
    forw = false;
    back = false;
    IntakeA.stop();
    IntakeB.stop();
  }

  void trapdoorScore() {
    if(TrapdoorA.value() && !TrapdoorB.value()) {
      TrapdoorA.set(false);
      TrapdoorB.set(false);
      intakeStop();
      intakeFwd();
      setCounter(-5); // quick rev
    } else {
      TrapdoorA.set(true);
      TrapdoorB.set(false);
    }
  }

  void trapdoorMidScore() {
  if(TrapdoorA.value() && !TrapdoorB.value()) {
    TrapdoorA.set(true);
    TrapdoorB.set(true);
    intakeStop();
    intakeFwd();
    setCounter(45);
  } else {
    TrapdoorA.set(true);
    TrapdoorB.set(false);
    setCounter(20);
  }
}

  void toggleSort() {
    if(colorSort == -1) {
      colorSort = 0;
    } else {
      colorSort = -1;
    }
  }

  void scheduleIntakeStop() {
    if(colorSort <= -2) {
      colorSort--;
      return;
    }
    colorSort = -2;
  }

  void toggleStall() {
    stall = !stall;
  }

  void setCounter(double count) {
    counter = count;
  }
};

#endif