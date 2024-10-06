#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT5, ratio6_1, true);
motor LeftDriveMotorB = motor(PORT6, ratio6_1, true);
motor LeftDriveMotorC = motor(PORT8, ratio6_1, true);
motor RightDriveMotorA = motor(PORT9, ratio6_1, false);
motor RightDriveMotorB = motor(PORT14, ratio6_1, false);
motor RightDriveMotorC = motor(PORT15, ratio6_1, false);

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor IntakeA = motor(PORT21, ratio18_1, true);
motor IntakeB = motor(PORT20, ratio18_1, false);
motor_group Intake = motor_group(IntakeA,IntakeB);

motor Arm = motor(PORT17, ratio18_1, true);
rotSub ArmRot = rotSub(PORT1, false);

inertial Inertial = inertial(PORT21,turnType::left);
optical Optical = optical(PORT1);
distance Distance = distance(PORT3);
rotSub Axial = rotSub(PORT3, false);
rotSub Axial2 = rotSub(PORT16, true);
rotSub Lateral = rotSub(PORT4, false);
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