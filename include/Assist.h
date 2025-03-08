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
  int newRing;
  double maxColor;
  double minColor;

  BreakTimer armB = BreakTimer(17,0.02);

  double mode;
  int loadDeg;
  PID armPID;

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

  double armRotation() {
    if(ArmRot.installed()) {
      return ArmRot.position(degrees);
    }
    return Arm.position(degrees);
  }

  double intakeRotation() {
    if(IntakeRot.installed()) {
      return IntakeRot.position(degrees);
    }
    return Intake.position(degrees);
  }

  void toggleArm() {
    Arm.setMaxTorque(100000000000,vex::currentUnits::amp);
    if(mode == 0) {
      armPID.start(loadDeg-armRotation());
      mode = -1;
    } else if(Controller1.ButtonY.pressing() && mode == 2) {
      armPID.start(650-armRotation());
      mode = 3;
    } else {
      armPID.start(-200-armRotation());
      intakeStop();
      mode = 0;
    }
  }

  void scoreArm() {
    armPID.start(0);
    Arm.setMaxTorque(100000000000,vex::currentUnits::amp);
    if(fabs(mode) == 1 || mode == 129) {
      mode = 2;
      armPID.start(440-armRotation());
      armB.reset();
    } else {
      armPID.start(650-armRotation());
      mode = 3;
    }
  }

  void setArmMode(int m) {
    armPID.start(m-armRotation());
    mode = m;
  }
};

#endif