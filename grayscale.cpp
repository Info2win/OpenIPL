#include "grayscale.h"


GrayScale::GrayScale(unsigned char& pIntensity)
{
    if(pIntensity < 0)
    {
        mIntensity = 0;
    }
    else if ( pIntensity > 255 )
    {
        mIntensity = 255;
    }
    else
    {
        mIntensity = pIntensity;
    }
}


unsigned char *GrayScale::getIntensity()
{
    return &mIntensity;
}


void GrayScale::setIntensity(unsigned char *pIntensity)
{
    if(*pIntensity < 0)
    {
        mIntensity = 0;
    }
    else if ( *pIntensity > 255 )
    {
        mIntensity = 255;
    }
    else
    {
        mIntensity = *pIntensity;
    }
}
