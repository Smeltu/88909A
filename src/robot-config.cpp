#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT6, ratio6_1, true);
motor LeftDriveMotorB = motor(PORT8, ratio6_1, true);
motor LeftDriveMotorC = motor(PORT10, ratio6_1, true);
motor RightDriveMotorA = motor(PORT17, ratio6_1, false);
motor RightDriveMotorB = motor(PORT15, ratio6_1, false);
motor RightDriveMotorC = motor(PORT20, ratio6_1, false);

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor IntakeA = motor(PORT5, ratio18_1, false);
motor IntakeB = motor(PORT12, ratio6_1, false);
motor_group Intake = motor_group(IntakeA,IntakeB);

motor Arm = motor(PORT9, ratio18_1, false);

inertial Inertial = inertial(PORT21,turnType::left);
optical Optical = optical(PORT1);
distance Distance = distance(PORT3);
rotSub Axial = rotSub(PORT4, false);
rotSub Lateral = rotSub(PORT2, false);
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