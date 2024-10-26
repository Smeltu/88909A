#ifndef __constants__
#define __constants__

const double PI = 3.1415926535897932384626433832795;
const double oDegreesToInches = 0.01732959851; //odometry dti 0.0174
const double degreesToInches = (Axial.installed() || Axial2.installed()) ? oDegreesToInches : 0.0180; //motor dti (odom if axial exists)
const double oDegreesToHeading = 0.1664823874; //converting between dTheta of two parallel pods to heading
const double oOffset = 4.8283; //odometry pod offset
const double oOffsetAngle = 201.2505055; //odometry pod offset angle
const double inertialCal = 1.008109478; //inertial sensor angle multiplier
extern int autonMode;

#endif