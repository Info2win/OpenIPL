#include "rgb.h"

Rgb::Rgb(unsigned char& pR, unsigned char& pG,unsigned char& pB)
{
    // R
    if(pR > 255)
    {
        mR = 255;
    }
    else if(pR < 0)
    {
        mR = 0;
    }
    else
    {
        mR = pR;
    }

    // G
    if(pG > 255)
    {
        mG = 255;
    }
    else if(pG < 0)
    {
        mG = 0;
    }
    else
    {
        mG = pG;
    }

    // B
    if(pB > 255)
    {
        mB = 255;
    }
    else if( pB < 0)
    {
        mB = 0;
    }
    else
    {
        mB = pB;
    }
}

unsigned char* Rgb::getR()
{
        return &mR;

}


unsigned char* Rgb::getG()
{
        return &mG;
}

unsigned char* Rgb::getB()
{
        return &mB;

}




