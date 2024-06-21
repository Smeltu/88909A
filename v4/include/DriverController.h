#ifndef __DRIVER_CONTROLLER__
#define __DRIVER_CONTROLLER__

class DriverController {
  private: void RunDriveTrain();
  void RunIntake();

  public: DriverController();
  void resetDriveMotors();
  void resetAll();
  void Run(vex::competition Competition);
};

#endif