#ifndef __ROTSUB__
#define __ROTSUB__

using namespace vex;

#include "constants.h"

extern inertial Inertial;

class rotSub : public vex::rotation {

    private:
        double xOffset;
        double yOffset; 
        bool axial;
    public:
        rotSub(int32_t index, bool reverse = false, double xOff = 0, double yOff = 0, bool axi = true):
            rotation(index, reverse),
            xOffset(xOff),
            yOffset(yOff),
            axial(axi) {}

        void setdatarate( uint32_t rate) {
            datarate(rate);
        }
        
        double getRotation() {
            return (Inertial.rotation() - setRotation) * inertialCal + setRotation;
        }

        double getPosition() {
            double pos = position(vex::rotationUnits::deg);
            if(xOffset == 0 && yOffset == 0) {
                return pos;
            }
            double radius = ((getRotation() - setRotation) / 360.0) * (sqrt(xOffset*xOffset + yOffset*yOffset) * 2 * PI) / oDegreesToInches;
            
            if(axial) {
                radius *= cos(atan(fabs(yOffset/xOffset))) * -1 * ((xOffset >= 0) * 2 - 1);
            } else {
                radius *= sin(atan(fabs(yOffset/xOffset))) * ((yOffset >= 0) * 2 - 1);
            }

            return (pos - radius);
        }
};

#endif