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
        bool adjust;
    public:
        rotSub(int32_t index, bool reverse = false, double xOff = 0, double yOff = 0, bool axi = true, bool adj = false):
            rotation(index, reverse),
            xOffset(xOff), // +dx towards front of bot, +dy towards left of bot
            yOffset(yOff),
            axial(axi),
            adjust(adj) {}

        void setdatarate( uint32_t rate) {
            datarate(rate);
        }
        
        double getRotation() {
            return (Inertial.rotation() - setRotation) * inertialCal + setRotation;
        }

        double getPosition() {
            double pos = position(vex::rotationUnits::deg);
            if(!adjust) {
                return pos;
            }

            double rotationOffset = (getRotation() - setRotation) * PI / 180.0;
            if(axial) {
                return (pos - rotationOffset * yOffset / oDegreesToInches);
            } else {
                return (pos - rotationOffset * xOffset / oDegreesToInches);
            }
        }
};

#endif