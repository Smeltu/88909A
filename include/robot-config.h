#include "rotsub.h"
using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftFrontDriveMotorA;
extern motor LeftFrontDriveMotorB;
extern motor LeftBackDriveMotorA;
extern motor LeftBackDriveMotorB;
extern motor RightFrontDriveMotorA;
extern motor RightFrontDriveMotorB;
extern motor RightBackDriveMotorA;
extern motor RightBackDriveMotorB;

extern motor_group LeftFrontDrive;
extern motor_group LeftBackDrive;
extern motor_group RightFrontDrive;
extern motor_group RightBackDrive;

extern motor IntakeA;
extern motor IntakeB;
extern motor_group Intake;

extern motor Arm;

extern inertial Inertial;
extern rotSub Axial;
extern rotSub Lateral;
extern controller Controller1;
extern optical Optical;
extern distance Distance;

extern digital_out Hook;
extern digital_out Prop;
extern digital_out Endgame;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );