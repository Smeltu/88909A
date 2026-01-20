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

extern motor IntakeA;
extern motor IntakeB;
extern motor_group Intake;

extern inertial Inertial;
extern rotSub Axial;
extern rotSub Axial2;
extern rotSub Lateral;
extern controller Controller1;
extern optical Optical;
extern distance Distance;

extern digital_out Loader;
extern digital_out Wing;
extern digital_out TrapdoorA;
extern digital_out TrapdoorB;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );