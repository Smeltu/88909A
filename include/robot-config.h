#include "rotsub.h"
using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftDriveMotorA;
extern motor LeftDriveMotorB;
extern motor LeftDriveMotorC;
extern motor RightDriveMotorA;
extern motor RightDriveMotorB;
extern motor RightDriveMotorC;

extern motor_group LeftDrive;
extern motor_group RightDrive;

extern motor Intake;

extern inertial Inertial;
extern rotSub Axial;
extern rotSub Lateral;
extern controller Controller1;
extern optical Optical;
extern distance Distance;

extern digital_out Hook;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );