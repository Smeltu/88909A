#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT10, ratio6_1, true);
motor LeftDriveMotorB = motor(PORT21, ratio6_1, true);
motor LeftDriveMotorC = motor(PORT20, ratio6_1, true);
motor RightDriveMotorA = motor(PORT7, ratio6_1, false);
motor RightDriveMotorB = motor(PORT12, ratio6_1, false);
motor RightDriveMotorC = motor(PORT14, ratio6_1, false);

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor Intake = motor(PORT5, ratio18_1, false);

inertial Inertial = inertial(PORT15,turnType::left);
optical Optical = optical(PORT4);
distance Distance = distance(PORT9);
rotSub Axial = rotSub(PORT9, false);
rotSub Lateral = rotSub(PORT2, false);
controller Controller1 = controller(primary);
digital_out Hook = digital_out(Brain.ThreeWirePort.A);


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