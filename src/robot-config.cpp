#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT15, ratio6_1, true);
motor LeftDriveMotorB = motor(PORT8, ratio6_1, true);
motor LeftDriveMotorC = motor(PORT20, ratio6_1, false);
motor RightDriveMotorA = motor(PORT18, ratio6_1, false);
motor RightDriveMotorB = motor(PORT6, ratio6_1, false);
motor RightDriveMotorC = motor(PORT21, ratio6_1, true);

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor IntakeA = motor(PORT2, ratio18_1, false);
motor IntakeB = motor(PORT1, ratio18_1, true);
motor_group Intake = motor_group(IntakeA,IntakeB);

motor Arm = motor(PORT5, ratio18_1, false);
rotSub ArmRot = rotSub(PORT10, true);

inertial Inertial = inertial(PORT12,turnType::left);
optical Optical = optical(PORT7);
distance Distance = distance(PORT20);
rotSub Axial = rotSub(PORT3, false);
rotSub Axial2 = rotSub(PORT16, true);
rotSub Lateral = rotSub(PORT10, false);
controller Controller1 = controller(primary);
digital_out Hook = digital_out(Brain.ThreeWirePort.A);
digital_out Prop = digital_out(Brain.ThreeWirePort.C);
digital_out Endgame = digital_out(Brain.ThreeWirePort.E);
digital_out Doinker = digital_out(Brain.ThreeWirePort.G);

limit HookLimit = limit(Brain.ThreeWirePort.H);


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