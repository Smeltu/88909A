#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT10, ratio6_1, true); //10
motor LeftDriveMotorB = motor(PORT13, ratio6_1, false);  //13
motor LeftDriveMotorC = motor(PORT21, ratio6_1, true); //21
motor RightDriveMotorA = motor(PORT16, ratio6_1, false);
motor RightDriveMotorB = motor(PORT2, ratio6_1, true); //2
motor RightDriveMotorC = motor(PORT11, ratio6_1, false); //11

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor IntakeA = motor(PORT8, ratio6_1, true); //6
motor IntakeB = motor(PORT5, ratio18_1, false);
motor_group Intake = motor_group(IntakeA, IntakeB);

inertial Inertial = inertial(PORT6,turnType::left); //11
optical Optical = optical(PORT20);
distance Distance = distance(PORT17); //10
rotSub Axial = rotSub(PORT3, false, 0.75, -1, true);
rotSub Axial2 = rotSub(PORT1, true, 1, 1, true);
rotSub Lateral = rotSub(PORT19, true, -3.4375, 2, false); //0.75, -0.75
controller Controller1 = controller(primary);
digital_out Loader = digital_out(Brain.ThreeWirePort.A);
digital_out Wing = digital_out(Brain.ThreeWirePort.C);
digital_out TrapdoorA = digital_out(Brain.ThreeWirePort.E);
digital_out TrapdoorB = digital_out(Brain.ThreeWirePort.G);


// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}