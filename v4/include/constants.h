#ifndef __constants__
#define __constants__

const double PI = 3.1415926535897932384626433832795;
const double oDegreesToInches = 0.02454753006; //odometry dti
const double degreesToInches = Axial.installed() ? oDegreesToInches : 0.02023145095; //motor dti (odom if axial exists)
const double oOffset = 4.8283; //odometry pod offset (1.75 horiz, 4.5-0.2 vert)
const double oOffsetAngle = 201.2505055; //odometry pod offset angle
const double inertialCal = 1.0166; //offset for inertial sensor
extern double iBrightness; //initial brightness for optical
extern int autonMode;

#endif