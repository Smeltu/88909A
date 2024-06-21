#include "vex.h"

using namespace vex;

void drawLogo() {
    static const char* imageColors[] = {
        "#000000", "#beb4ab", "#766e69", "#2f2724", 
    };

    static const int imageIndices[] = {
        0, 1, 0, 1, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 1, 0, 1, 2, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 1, 2, 3, 1, 0, 1, 0, 1, 2, 3, 2, 1, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 1, 0, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 3, 2, 1, 0, 1, 2, 1, 0, 1, 0, 1, 0, 
    };

    static const int imageCounts[] = {
        712, 25, 453, 8, 16, 5, 446, 6, 11, 9, 7, 6, 436, 7, 5, 26, 5, 3, 430, 8, 4, 34, 3, 3, 418, 10, 10, 38, 4, 4, 412, 5, 7, 52, 2, 4, 407, 5, 6, 57, 4, 5, 400, 4, 6, 65, 4, 4, 395, 4, 3, 73, 3, 7, 383, 7, 5, 28, 12, 37, 8, 8, 374, 3, 5, 30, 15, 45, 6, 4, 368, 5, 4, 29, 7, 6, 15, 40, 5, 7, 359, 4, 4, 29, 7, 17, 13, 40, 5, 4, 356, 3, 3, 31, 4, 27, 11, 40, 4, 3, 351, 3, 4, 23, 12, 35, 13, 34, 5, 5, 345, 2, 2, 21, 12, 51, 7, 35, 3, 4, 340, 3, 3, 15, 14, 59, 13, 28, 4, 6, 333, 2, 4, 13, 8, 76, 12, 26, 5, 4, 329, 2, 2, 14, 6, 88, 5, 29, 4, 3, 323, 4, 3, 11, 6, 94, 5, 29, 5, 5, 318, 2, 2, 13, 3, 100, 3, 34, 4, 2, 314, 3, 3, 12, 4, 103, 3, 34, 4, 3, 309, 3, 2, 12, 4, 108, 3, 35, 3, 3, 306, 3, 1, 13, 3, 111, 3, 37, 2, 2, 303, 2, 3, 11, 5, 114, 4, 35, 3, 2, 299, 2, 2, 13, 3, 120, 5, 10, 2, 22, 1, 2, 297, 2, 2, 12, 4, 123, 8, 30, 2, 2, 293, 3, 2, 11, 5, 129, 5, 29, 3, 1, 292, 1, 2, 11, 5, 134, 3, 30, 2, 1, 289, 2, 2, 9, 7, 137, 4, 28, 2, 2, 286, 2, 2, 9, 6, 141, 3, 29, 2, 1, 284, 2, 1, 10, 6, 144, 3, 28, 2, 2, 281, 1, 2, 9, 6, 148, 3, 27, 2, 2, 279, 1, 2, 9, 5, 152, 3, 26, 2, 2, 276, 2, 2, 8, 6, 154, 5, 24, 2, 2, 274, 2, 1, 9, 6, 158, 4, 24, 1, 1, 273, 2, 2, 8, 5, 162, 4, 22, 2, 1, 270, 2, 2, 8, 6, 166, 3, 21, 2, 1, 268, 2, 2, 8, 6, 168, 3, 21, 1, 2, 266, 2, 2, 8, 5, 172, 4, 19, 2, 2, 263, 2, 1, 9, 6, 174, 3, 19, 2, 2, 261, 2, 2, 8, 6, 177, 3, 18, 2, 2, 259, 2, 1, 9, 6, 180, 4, 16, 2, 2, 257, 2, 2, 8, 6, 183, 3, 16, 2, 2, 255, 2, 2, 8, 6, 186, 4, 14, 2, 1, 254, 2, 1, 9, 6, 189, 3, 14, 1, 2, 253, 1, 2, 8, 7, 190, 3, 14, 1, 2, 251, 1, 1, 9, 6, 138, 19, 36, 2, 14, 2, 1, 250, 2, 1, 8, 6, 136, 24, 34, 2, 15, 2, 1, 248, 2, 1, 8, 7, 131, 32, 32, 3, 14, 1, 2, 247, 1, 1, 8, 6, 131, 5, 8, 12, 7, 4, 31, 2, 14, 2, 2, 245, 1, 2, 7, 7, 128, 40, 31, 2, 14, 2, 1, 244, 2, 1, 7, 7, 126, 17, 16, 11, 31, 2, 3, 3, 7, 2, 2, 243, 1, 1, 8, 6, 126, 3, 5, 5, 25, 8, 31, 2, 2, 4, 7, 2, 2, 241, 1, 2, 6, 7, 124, 13, 31, 4, 33, 1, 2, 5, 7, 2, 2, 239, 2, 1, 7, 6, 123, 4, 2, 5, 72, 6, 1, 1, 9, 1, 1, 238, 2, 2, 6, 6, 122, 11, 75, 5, 1, 2, 8, 2, 1, 237, 1, 2, 6, 6, 121, 10, 79, 3, 3, 2, 7, 3, 1, 235, 2, 1, 6, 6, 121, 4, 2, 3, 82, 2, 4, 1, 9, 1, 1, 234, 2, 1, 6, 6, 120, 10, 89, 2, 8, 1, 2, 233, 1, 2, 6, 5, 120, 3, 2, 3, 93, 1, 5, 1, 3, 1, 1, 232, 2, 1, 6, 3, 122, 8, 94, 2, 4, 2, 2, 1, 2, 230, 2, 1, 6, 3, 121, 8, 96, 2, 4, 2, 2, 1, 2, 230, 1, 2, 6, 2, 121, 4, 1, 3, 98, 2, 3, 6, 1, 229, 1, 2, 6, 3, 119, 8, 100, 2, 4, 5, 2, 227, 2, 1, 6, 2, 120, 4, 1, 2, 103, 1, 4, 6, 1, 226, 2, 1, 6, 2, 120, 7, 104, 1, 5, 5, 1, 226, 1, 2, 6, 2, 119, 7, 105, 1, 5, 3, 1, 1, 1, 226, 1, 1, 6, 2, 120, 6, 106, 1, 5, 3, 1, 1, 1, 224, 2, 1, 6, 2, 119, 7, 107, 2, 4, 3, 1, 2, 1, 223, 1, 2, 6, 1, 119, 6, 109, 2, 4, 3, 1, 2, 2, 221, 1, 2, 6, 2, 118, 6, 111, 1, 4, 3, 1, 3, 1, 221, 1, 1, 6, 2, 118, 6, 112, 1, 4, 3, 2, 2, 1, 220, 1, 1, 7, 1, 119, 5, 113, 2, 4, 2, 3, 1, 1, 219, 2, 1, 6, 3, 116, 6, 114, 2, 4, 2, 3, 1, 1, 219, 1, 1, 6, 4, 115, 6, 115, 2, 5, 2, 3, 1, 1, 217, 1, 1, 6, 6, 114, 5, 117, 1, 5, 3, 2, 1, 1, 216, 2, 1, 5, 7, 113, 5, 118, 2, 4, 3, 2, 1, 2, 214, 2, 1, 6, 7, 112, 5, 120, 1, 4, 4, 1, 2, 1, 214, 1, 2, 5, 7, 112, 5, 121, 1, 4, 7, 2, 213, 1, 1, 6, 4, 1, 1, 112, 5, 122, 1, 4, 8, 1, 212, 1, 1, 6, 7, 112, 5, 74, 6, 42, 2, 4, 2, 2, 3, 1, 211, 2, 1, 5, 8, 110, 5, 72, 12, 40, 2, 4, 2, 3, 2, 1, 211, 1, 1, 6, 8, 110, 5, 71, 4, 8, 3, 39, 1, 5, 1, 3, 1, 2, 210, 2, 1, 6, 3, 1, 3, 110, 5, 69, 5, 12, 3, 37, 2, 4, 1, 7, 209, 1, 1, 6, 4, 2, 2, 110, 4, 69, 2, 18, 2, 36, 2, 4, 1, 8, 207, 2, 1, 5, 5, 1, 2, 110, 4, 68, 3, 19, 3, 35, 2, 4, 2, 2, 2, 2, 208, 1, 1, 6, 4, 2, 2, 109, 5, 67, 3, 10, 4, 8, 1, 36, 1, 5, 1, 2, 3, 1, 207, 1, 2, 5, 4, 3, 1, 109, 5, 68, 1, 11, 2, 1, 3, 7, 2, 35, 1, 5, 2, 1, 211, 1, 1, 6, 3, 3, 2, 109, 4, 67, 2, 11, 3, 3, 3, 6, 2, 34, 1, 5, 2, 1, 210, 2, 1, 6, 3, 2, 3, 108, 5, 66, 2, 11, 2, 7, 2, 5, 2, 34, 2, 4, 2, 1, 209, 2, 1, 6, 4, 2, 2, 108, 5, 66, 2, 10, 3, 9, 1, 6, 1, 35, 1, 5, 1, 1, 209, 2, 1, 5, 4, 3, 1, 109, 4, 66, 2, 9, 3, 11, 2, 5, 2, 34, 1, 5, 1, 1, 209, 1, 2, 5, 3, 4, 1, 108, 5, 66, 1, 9, 2, 14, 2, 4, 2, 34, 1, 5, 2, 1, 208, 1, 1, 5, 4, 3, 2, 107, 5, 65, 3, 9, 1, 15, 2, 4, 2, 34, 2, 4, 2, 1, 207, 1, 1, 6, 3, 3, 2, 108, 5, 65, 1, 10, 2, 16, 1, 4, 2, 34, 2, 5, 1, 1, 207, 1, 1, 5, 4, 3, 2, 107, 5, 65, 2, 9, 2, 17, 1, 4, 2, 34, 2, 5, 1, 2, 205, 2, 1, 5, 3, 3, 2, 108, 4, 66, 2, 8, 2, 18, 2, 3, 2, 35, 1, 5, 1, 2, 205, 1, 2, 5, 2, 4, 2, 107, 5, 66, 2, 8, 1, 19, 2, 3, 2, 35, 2, 4, 1, 2, 204, 2, 1, 6, 2, 3, 2, 108, 4, 67, 2, 7, 2, 20, 1, 3, 2, 35, 2, 4, 1, 2, 204, 1, 1, 6, 3, 3, 2, 107, 4, 68, 2, 6, 2, 21, 2, 3, 1, 35, 2, 4, 2, 1, 204, 1, 1, 6, 3, 2, 2, 108, 4, 32, 14, 21, 2, 6, 2, 22, 2, 3, 2, 35, 1, 4, 2, 1, 204, 1, 1, 5, 4, 2, 1, 108, 4, 29, 7, 10, 4, 17, 2, 6, 3, 15, 5, 2, 2, 3, 2, 35, 1, 4, 2, 2, 202, 1, 1, 5, 5, 1, 2, 107, 5, 27, 3, 18, 3, 15, 2, 7, 1, 16, 6, 1, 3, 3, 2, 35, 1, 5, 1, 2, 201, 2, 1, 5, 8, 107, 4, 26, 3, 22, 6, 9, 2, 7, 2, 15, 2, 4, 6, 1, 3, 35, 1, 5, 1, 2, 201, 2, 1, 5, 3, 1, 3, 107, 4, 26, 2, 28, 4, 5, 2, 8, 2, 15, 2, 5, 2, 3, 4, 36, 1, 5, 1, 2, 201, 1, 2, 5, 3, 1, 2, 108, 4, 26, 1, 31, 8, 8, 2, 16, 1, 6, 2, 4, 1, 38, 1, 5, 2, 1, 201, 1, 1, 5, 4, 1, 2, 107, 5, 24, 3, 34, 3, 9, 2, 16, 2, 5, 2, 44, 1, 5, 2, 1, 201, 1, 6, 6, 107, 5, 25, 2, 46, 2, 17, 2, 5, 2, 44, 1, 6, 1, 1, 200, 1, 1, 5, 7, 107, 5, 24, 2, 46, 2, 18, 2, 4, 2, 45, 2, 5, 1, 1, 199, 2, 1, 5, 6, 108, 4, 25, 1, 14, 8, 24, 2, 19, 7, 46, 2, 5, 1, 1, 199, 2, 1, 4, 7, 107, 4, 25, 2, 9, 9, 1, 5, 21, 2, 21, 5, 47, 2, 5, 1, 1, 199, 1, 2, 4, 6, 108, 4, 25, 1, 8, 3, 12, 5, 16, 3, 74, 2, 5, 1, 1, 198, 2, 1, 5, 5, 108, 5, 25, 1, 7, 2, 17, 4, 13, 2, 76, 2, 5, 1, 1, 198, 1, 2, 5, 5, 108, 4, 25, 2, 6, 2, 20, 5, 8, 3, 77, 2, 5, 1, 1, 198, 1, 1, 5, 5, 109, 3, 26, 1, 6, 2, 25, 4, 2, 4, 79, 2, 5, 1, 1, 198, 1, 1, 5, 3, 110, 4, 26, 1, 6, 2, 27, 7, 80, 2, 5, 1, 1, 198, 1, 1, 5, 3, 110, 4, 26, 1, 6, 2, 114, 2, 5, 1, 1, 197, 1, 1, 5, 4, 109, 5, 26, 1, 5, 3, 114, 2, 5, 1, 1, 197, 1, 1, 5, 3, 110, 4, 27, 1, 5, 2, 115, 3, 4, 1, 1, 196, 2, 1, 5, 3, 109, 5, 27, 1, 5, 1, 117, 2, 4, 1, 2, 195, 2, 1, 5, 2, 110, 4, 28, 1, 4, 2, 117, 2, 4, 1, 2, 195, 2, 1, 4, 2, 111, 4, 28, 2, 3, 2, 117, 2, 4, 1, 2, 195, 1, 2, 4, 2, 111, 3, 30, 5, 118, 2, 4, 1, 2, 195, 1, 2, 4, 2, 110, 4, 30, 5, 118, 2, 4, 2, 2, 194, 1, 2, 4, 2, 109, 5, 153, 2, 4, 2, 2, 194, 1, 1, 5, 1, 110, 5, 58, 7, 56, 2, 30, 2, 4, 2, 2, 194, 1, 1, 4, 2, 110, 4, 58, 3, 3, 3, 54, 4, 30, 1, 4, 2, 2, 194, 1, 1, 4, 2, 110, 4, 58, 1, 6, 2, 53, 2, 1, 3, 29, 1, 5, 1, 2, 194, 1, 1, 4, 2, 109, 4, 58, 2, 6, 2, 53, 1, 2, 3, 29, 2, 4, 1, 2, 194, 1, 1, 4, 2, 109, 4, 58, 2, 5, 2, 53, 2, 3, 2, 29, 2, 4, 1, 2, 194, 1, 5, 2, 108, 5, 58, 3, 1, 5, 53, 2, 3, 1, 30, 2, 4, 1, 2, 193, 1, 1, 5, 2, 108, 5, 59, 6, 54, 2, 3, 2, 30, 2, 4, 1, 2, 193, 1, 1, 5, 2, 107, 6, 119, 2, 3, 2, 30, 2, 4, 1, 2, 193, 1, 1, 5, 1, 108, 5, 120, 1, 4, 1, 31, 2, 4, 1, 2, 193, 1, 1, 4, 2, 108, 5, 120, 1, 3, 2, 31, 1, 5, 1, 2, 193, 1, 1, 4, 2, 108, 1, 1, 3, 119, 2, 3, 2, 31, 1, 5, 1, 2, 193, 1, 1, 4, 2, 107, 2, 1, 2, 119, 2, 4, 2, 31, 1, 5, 1, 2, 193, 1, 1, 4, 2, 107, 2, 1, 2, 119, 2, 3, 2, 32, 1, 5, 1, 2, 193, 1, 1, 4, 2, 106, 3, 1, 2, 118, 2, 4, 2, 32, 2, 4, 1, 2, 193, 1, 1, 4, 2, 106, 3, 1, 2, 118, 2, 4, 1, 33, 2, 4, 1, 2, 192, 2, 1, 4, 2, 106, 3, 1, 1, 118, 2, 4, 2, 33, 2, 4, 1, 2, 192, 2, 1, 4, 2, 106, 1, 1, 3, 117, 3, 3, 2, 34, 2, 4, 1, 2, 192, 2, 1, 4, 2, 105, 2, 1, 3, 117, 2, 4, 2, 34, 1, 5, 1, 2, 192, 2, 1, 4, 2, 105, 2, 1, 3, 61, 6, 49, 2, 4, 2, 35, 1, 5, 2, 1, 192, 1, 2, 4, 2, 105, 1, 2, 2, 61, 2, 3, 3, 47, 2, 5, 1, 36, 1, 6, 1, 2, 191, 1, 2, 4, 2, 105, 1, 2, 2, 61, 1, 5, 2, 47, 2, 4, 2, 36, 1, 7, 1, 1, 191, 1, 2, 4, 2, 105, 1, 2, 2, 60, 2, 5, 2, 46, 2, 4, 2, 37, 1, 7, 1, 1, 191, 1, 2, 4, 2, 104, 2, 2, 1, 61, 1, 6, 2, 45, 2, 5, 1, 37, 2, 7, 1, 1, 191, 1, 2, 4, 2, 104, 2, 2, 1, 61, 1, 7, 3, 42, 2, 5, 2, 36, 3, 7, 1, 1, 191, 1, 2, 4, 2, 103, 3, 2, 1, 61, 1, 8, 2, 41, 2, 5, 2, 37, 2, 7, 1, 1, 192, 1, 2, 4, 2, 103, 2, 3, 1, 61, 2, 8, 3, 37, 3, 5, 2, 37, 2, 7, 2, 1, 192, 1, 2, 4, 2, 103, 2, 3, 1, 62, 2, 9, 3, 34, 3, 5, 2, 38, 2, 7, 1, 2, 192, 1, 2, 4, 2, 103, 1, 3, 2, 63, 2, 9, 3, 32, 2, 6, 3, 38, 2, 6, 2, 2, 192, 1, 2, 4, 2, 103, 1, 3, 2, 64, 3, 9, 3, 27, 4, 7, 2, 39, 2, 6, 1, 2, 193, 1, 2, 4, 2, 103, 1, 3, 2, 66, 2, 9, 3, 25, 3, 8, 2, 40, 2, 5, 2, 1, 194, 1, 2, 4, 2, 103, 1, 2, 3, 67, 2, 10, 4, 19, 5, 7, 3, 40, 3, 5, 1, 2, 194, 1, 2, 4, 2, 103, 1, 2, 3, 69, 2, 11, 5, 12, 5, 9, 3, 41, 2, 6, 1, 2, 194, 1, 2, 4, 2, 103, 1, 2, 2, 71, 2, 12, 18, 10, 2, 43, 2, 6, 1, 2, 194, 1, 2, 4, 2, 102, 2, 2, 2, 72, 3, 14, 11, 11, 3, 44, 1, 7, 1, 2, 194, 1, 2, 4, 2, 102, 2, 2, 2, 74, 3, 33, 2, 46, 1, 7, 1, 2, 194, 2, 1, 5, 1, 102, 2, 2, 2, 75, 4, 29, 3, 46, 2, 6, 2, 2, 194, 2, 1, 5, 2, 101, 1, 3, 2, 78, 4, 23, 5, 47, 2, 6, 2, 2, 194, 2, 1, 5, 2, 100, 2, 3, 2, 80, 5, 18, 4, 50, 1, 7, 2, 2, 194, 2, 1, 5, 2, 100, 2, 3, 2, 82, 8, 10, 6, 50, 2, 7, 2, 2, 195, 1, 1, 5, 2, 100, 2, 3, 1, 88, 15, 54, 2, 7, 2, 2, 195, 1, 1, 5, 2, 100, 2, 3, 1, 90, 11, 56, 2, 7, 2, 1, 196, 1, 1, 5, 2, 100, 2, 3, 1, 139, 7, 10, 2, 8, 2, 1, 196, 1, 1, 5, 2, 100, 2, 3, 1, 137, 10, 9, 2, 8, 1, 2, 196, 1, 1, 5, 2, 100, 2, 3, 1, 135, 4, 6, 2, 9, 1, 9, 1, 2, 196, 1, 1, 5, 2, 100, 2, 3, 1, 134, 2, 10, 1, 9, 1, 9, 1, 1, 197, 1, 1, 5, 2, 100, 2, 3, 1, 132, 3, 10, 2, 8, 2, 9, 1, 1, 197, 1, 1, 6, 1, 100, 2, 3, 1, 131, 2, 11, 2, 8, 2, 9, 1, 1, 198, 1, 1, 6, 2, 99, 2, 3, 1, 129, 3, 11, 2, 9, 2, 9, 1, 1, 199, 1, 1, 6, 2, 98, 2, 3, 1, 124, 7, 11, 2, 10, 1, 9, 2, 1, 199, 1, 1, 6, 4, 96, 2, 3, 1, 122, 4, 15, 2, 10, 2, 8, 2, 2, 199, 2, 1, 6, 3, 96, 2, 3, 2, 120, 3, 17, 1, 11, 1, 9, 1, 2, 200, 2, 1, 7, 2, 97, 1, 3, 2, 120, 1, 19, 1, 11, 1, 8, 2, 1, 202, 2, 1, 6, 2, 97, 1, 3, 2, 119, 2, 19, 1, 10, 2, 8, 1, 2, 203, 1, 1, 6, 2, 97, 2, 3, 2, 117, 2, 20, 2, 8, 2, 8, 1, 2, 204, 1, 1, 5, 2, 99, 1, 3, 2, 117, 2, 21, 2, 7, 2, 8, 1, 1, 205, 1, 1, 6, 2, 98, 1, 4, 1, 116, 2, 23, 2, 5, 2, 8, 1, 1, 206, 1, 1, 6, 3, 97, 2, 3, 1, 115, 2, 25, 7, 8, 1, 2, 206, 1, 1, 7, 2, 97, 3, 2, 2, 113, 2, 27, 4, 9, 2, 1, 207, 1, 2, 7, 2, 97, 5, 112, 3, 40, 2, 1, 208, 2, 1, 7, 2, 99, 2, 112, 2, 41, 2, 2, 209, 2, 1, 7, 3, 208, 4, 42, 1, 2, 211, 2, 1, 7, 4, 204, 4, 14, 6, 23, 1, 2, 213, 1, 2, 8, 4, 201, 3, 15, 2, 5, 2, 20, 1, 2, 215, 2, 2, 8, 6, 194, 4, 14, 3, 3, 3, 3, 11, 7, 2, 2, 217, 2, 2, 11, 6, 189, 3, 13, 3, 3, 9, 8, 7, 2, 2, 2, 219, 2, 2, 12, 8, 183, 4, 12, 3, 4, 13, 11, 3, 3, 221, 2, 2, 17, 8, 136, 4, 34, 4, 14, 2, 3, 25, 6, 225, 2, 1, 20, 7, 132, 6, 32, 3, 15, 2, 2, 259, 2, 4, 20, 9, 125, 2, 3, 2, 28, 6, 13, 3, 3, 263, 2, 3, 24, 5, 123, 1, 5, 1, 27, 4, 15, 2, 2, 267, 3, 5, 22, 7, 118, 2, 5, 1, 25, 4, 14, 3, 3, 270, 6, 5, 22, 7, 113, 2, 5, 1, 22, 4, 15, 3, 3, 277, 4, 5, 23, 5, 110, 2, 5, 2, 20, 4, 16, 2, 2, 282, 7, 7, 19, 7, 105, 2, 5, 2, 16, 6, 15, 3, 4, 290, 4, 5, 21, 4, 103, 1, 6, 2, 14, 5, 17, 2, 2, 296, 6, 5, 19, 5, 51, 1, 48, 1, 6, 2, 5, 3, 3, 6, 16, 3, 3, 301, 7, 4, 19, 5, 44, 5, 47, 1, 6, 2, 3, 11, 17, 2, 4, 309, 3, 5, 18, 5, 42, 2, 2, 2, 45, 2, 6, 2, 1, 10, 19, 2, 2, 313, 6, 6, 16, 6, 37, 2, 4, 2, 43, 2, 7, 5, 23, 4, 3, 320, 4, 4, 18, 4, 34, 2, 6, 2, 42, 2, 8, 2, 23, 3, 3, 325, 5, 5, 16, 5, 31, 2, 6, 2, 42, 1, 32, 3, 3, 331, 6, 4, 15, 5, 28, 2, 7, 1, 41, 2, 29, 3, 4, 338, 3, 3, 17, 3, 27, 2, 7, 2, 40, 2, 28, 2, 2, 343, 5, 4, 15, 7, 21, 2, 8, 2, 38, 2, 18, 4, 3, 4, 4, 349, 2, 3, 17, 5, 19, 2, 9, 1, 38, 2, 17, 9, 2, 355, 3, 4, 17, 7, 11, 4, 10, 2, 36, 2, 15, 3, 10, 358, 5, 3, 18, 15, 14, 2, 34, 2, 13, 3, 4, 4, 3, 364, 3, 2, 22, 8, 17, 2, 32, 2, 12, 3, 2, 376, 4, 4, 44, 2, 30, 2, 11, 2, 4, 381, 3, 3, 43, 2, 28, 2, 10, 2, 2, 387, 3, 5, 40, 2, 26, 2, 11, 1, 2, 390, 6, 4, 37, 2, 25, 1, 11, 1, 1, 397, 3, 4, 35, 2, 24, 2, 11, 1, 1, 398, 6, 6, 11, 6, 13, 2, 19, 3, 2, 1, 10, 1, 2, 404, 5, 5, 7, 1, 4, 2, 13, 1, 17, 6, 1, 1, 9, 1, 2, 407, 6, 10, 5, 2, 12, 2, 15, 3, 2, 4, 9, 1, 2, 411, 10, 1, 4, 1, 2, 2, 12, 2, 13, 2, 5, 2, 10, 1, 1, 421, 6, 3, 1, 2, 11, 2, 12, 2, 18, 1, 423, 6, 2, 2, 2, 11, 5, 4, 5, 18, 1, 1, 424, 6, 2, 2, 1, 14, 8, 20, 2, 1, 424, 6, 2, 3, 2, 14, 3, 23, 1, 2, 426, 4, 2, 4, 2, 38, 1, 2, 428, 3, 2, 6, 1, 37, 1, 1, 438, 3, 3, 32, 2, 2, 441, 3, 2, 30, 1, 1, 445, 2, 3, 26, 2, 1, 448, 4, 5, 5, 4, 10, 2, 2, 451, 5, 20, 2, 455, 24, 473, 4, 1187, 
    };
    int x = 0, y = 0;
    for(int i = 0; i < sizeof(imageIndices) / sizeof(imageIndices[0]); ++i) {
        int index = imageIndices[i];
        int count = imageCounts[i];
        if(index >= 0) {
            const char* color = imageColors[index];
            Brain.Screen.setPenColor(color);
            for(int j = 0; j < count; ++j) {
                Brain.Screen.drawPixel(x++, y);
                if(x >= 480) { x = 0; y++; }
            }
        } else {
            x += count;
            while(x >= 480) { x -= 480; y++; }
        }
    }
}
