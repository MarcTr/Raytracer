#ifndef COLORS_H
#define COLORS_H

#include "RGBType.h"

namespace Utility 
{
    struct Colors 
    {
        RGBType background = RGBType(1, 1, 1);
        RGBType lightgrey = RGBType(0.9, 0.9, 0.9);
        RGBType red = RGBType(0.5, 0, 0);
        RGBType blue = RGBType(0, 0.5, 0);
        RGBType green = RGBType(0, 0, 0.5);
        RGBType black = RGBType(0, 0, 0);
        RGBType white = RGBType(1, 1, 1);
    };
}

#endif