#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftFrontDriveMotorA = motor(PORT21, ratio6_1, true);
motor LeftFrontDriveMotorB = motor(PORT20, ratio6_1, true);
motor LeftBackDriveMotorA = motor(PORT6, ratio6_1, false);
motor LeftBackDriveMotorB = motor(PORT10, ratio6_1, false);
motor RightFrontDriveMotorA = motor(PORT12, ratio6_1, false);
motor RightFrontDriveMotorB = motor(PORT17, ratio6_1, false);
motor RightBackDriveMotorA = motor(PORT14, ratio6_1, true);
motor RightBackDriveMotorB = motor(PORT18, ratio6_1, true);
motor_group LeftFrontDrive = motor_group(RightFrontDriveMotorA, RightFrontDriveMotorB);
motor_group LeftBackDrive = motor_group(RightBackDriveMotorA, RightBackDriveMotorB);
motor_group RightFrontDrive = motor_group(RightFrontDriveMotorA, RightFrontDriveMotorB);
motor_group RightBackDrive = motor_group(RightBackDriveMotorA, RightBackDriveMotorB);

motor IntakeA = motor(PORT1, ratio18_1, false);
motor IntakeB = motor(PORT2, ratio6_1, false);
motor_group Intake = motor_group(IntakeA,IntakeB);

motor Arm = motor(PORT3, ratio18_1, false);

inertial Inertial = inertial(PORT21,turnType::left);
optical Optical = optical(PORT4);
distance Distance = distance(PORT8);
rotSub Axial = rotSub(PORT9, false);
rotSub Lateral = rotSub(PORT11, false);
controller Controller1 = controller(primary);
digital_out Hook = digital_out(Brain.ThreeWirePort.A);
digital_out Prop = digital_out(Brain.ThreeWirePort.C);
digital_out Endgame = digital_out(Brain.ThreeWirePort.G);


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