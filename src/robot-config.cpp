#include "vex.h"
#include "rotsub.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveMotorA = motor(PORT16, ratio6_1, true);
motor LeftDriveMotorB = motor(PORT17, ratio6_1, true);
motor LeftDriveMotorC = motor(PORT20, ratio6_1, false);
motor RightDriveMotorA = motor(PORT2, ratio6_1, false);
motor RightDriveMotorB = motor(PORT8, ratio6_1, false);
motor RightDriveMotorC = motor(PORT14, ratio6_1, true);

motor_group LeftDrive = motor_group(LeftDriveMotorA, LeftDriveMotorB, LeftDriveMotorC);
motor_group RightDrive = motor_group(RightDriveMotorA, RightDriveMotorB, RightDriveMotorC);

motor IntakeA = motor(PORT6, ratio18_1, false);
motor IntakeB = motor(PORT5, ratio18_1, false);
motor_group Intake = motor_group(IntakeA,IntakeB);
rotSub IntakeRot = rotSub(PORT3, false);

motor Arm = motor(PORT12, ratio18_1, true); // 5
rotSub ArmRot = rotSub(PORT1, false); // 16

inertial Inertial = inertial(PORT11,turnType::left);
optical Optical = optical(PORT13);
distance Distance = distance(PORT21);
rotSub Axial = rotSub(PORT9, true, -1.5, -2.25, true); //-1.5, -2.25
rotSub Axial2 = rotSub(PORT16, true, 1, 1, true);
rotSub Lateral = rotSub(PORT7, false, 0.75, -0.75, false); //0.75, -0.75
controller Controller1 = controller(primary);
digital_out Hook = digital_out(Brain.ThreeWirePort.A);
digital_out Prop = digital_out(Brain.ThreeWirePort.B); //not existent
digital_out Doinker = digital_out(Brain.ThreeWirePort.C);
digital_out Endgame = digital_out(Brain.ThreeWirePort.D); //not existent
digital_out DoinkerClaw = digital_out(Brain.ThreeWirePort.E); //not existent

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