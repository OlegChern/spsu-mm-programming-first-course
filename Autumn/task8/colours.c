#include "colours.h"

#define multiply() result.red = arg.red * value; result.green = arg.green * value; result.blue = arg.blue * value

RealColour multiplyBE24(BigEndianColour24 arg, double value)
{
    RealColour result;
    multiply();
    // result.aplha = 0;
    return result;
}

RealColour multiplyBE32(BigEndianColour32 arg, double value)
{
    RealColour result;
    multiply();
    result.alpha = arg.alpha * value;
    return result;
}

RealColour multiplyLE24(LittleEndianColour24 arg, double value)
{
    RealColour result;
    multiply();
    // result.alpha = 0;
    return result;
}

RealColour multiplyLE32(LittleEndianColour32 arg, double value)
{
    RealColour result;
    multiply();
    result.alpha = arg.alpha * value;
    return result;
}

void addToColour(RealColour *first, RealColour second)
{
    first->red += second.red;
    first->green += second.green;
    first->blue += second.blue;
    first->alpha += second.alpha;
}
