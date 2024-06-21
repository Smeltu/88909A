#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT16, ratio6_1, true);
motor LeftDriveMotorB = motor(PORT11, ratio6_1, false);
motor LeftDriveMotorC = motor(PORT13, ratio6_1, true);
motor RightDriveMotorA = motor(PORT4, ratio6_1, false);
motor RightDriveMotorB = motor(PORT8, ratio6_1, true);
motor RightDriveMotorC = motor(PORT6, ratio6_1, false);

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor Intake = motor(PORT21, ratio6_1, false);//21
motor SlapperA = motor(PORT19, ratio18_1, true);//18
motor SlapperB = motor(PORT10, ratio18_1, false);
motor_group Slapper = motor_group(SlapperA, SlapperB);

inertial Inertial = inertial(PORT15,turnType::left);
optical Optical = optical(PORT4);
distance Distance = distance(PORT9);
rotSub Axial = rotSub(PORT9, false);
rotSub Lateral = rotSub(PORT2, false);
controller Controller1 = controller(primary);
digital_out Wings = digital_out(Brain.ThreeWirePort.A);
digital_out Pto = digital_out(Brain.ThreeWirePort.G);


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