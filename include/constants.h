#ifndef __constants__
#define __constants__

const double PI = 3.1415926535897932384626433832795;
const double oDegreesToInches = 0.02454753006; //odometry dti
const double degreesToInches = Axial.installed() ? oDegreesToInches : 0.0180; //motor dti (odom if axial exists)
const double oDegreesToHeading = 1; //converting between dTheta of two parallel pods to heading
const double oOffset = 4.8283; //odometry pod offset
const double oOffsetAngle = 201.2505055; //odometry pod offset angle
const double inertialCal = 1.0166; //inertial sensor angle multiplier
extern int autonMode;

#endif