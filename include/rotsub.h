#ifndef __ROTSUB__
#define __ROTSUB__

using namespace vex;

class rotSub : public vex::rotation {
    public:
        rotSub(int32_t index, bool reverse = false) : rotation(index, reverse) {
            
        }
        void setdatarate( uint32_t rate) {
            datarate(rate);
        }
};

#endif