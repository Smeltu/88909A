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

motor IntakeA = motor(PORT8, ratio18_1, true); //6
motor IntakeB = motor(PORT4, ratio18_1, false);
motor_group Intake = motor_group(IntakeA,IntakeB);
rotSub IntakeRot = rotSub(PORT14, false);

motor Arm = motor(PORT15, ratio18_1, true); // 5
rotSub ArmRot = rotSub(PORT1, false); // 16

inertial Inertial = inertial(PORT6,turnType::left); //11
optical Optical = optical(PORT20);
distance Distance = distance(PORT17); //10
rotSub Axial = rotSub(PORT3, false, 0.25, -1.35, true);
rotSub Axial2 = rotSub(PORT1, true, 1, 1, true);
rotSub Lateral = rotSub(PORT19, true, -3.4375, 2, false); //0.75, -0.75
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