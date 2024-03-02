#include "rgba.h"



Rgba::Rgba(Rgb pRgb, unsigned char pA) : mRgb(pRgb)
{
    if(pA>255)
    {
        mA = 255;
    }
    else if(pA < 0)
    {
        mA = 0;
    }
    else
    {
        mA = pA;
    }

}

Rgba::Rgba(unsigned char pR, unsigned char pG, unsigned char pB, unsigned char pA) : mRgb(pR,pG,pB)
{
    if(pA>255)
    {
        mA = 255;
    }
    else if(pA < 0)
    {
        mA = 0;
    }
    else
    {
        mA = pA;
    }
}

Rgb* Rgba::getRgb()
{
    return &mRgb;
}

unsigned char *Rgba::getR()
{
    return mRgb.getR();
}

unsigned char *Rgba::getG()
{
    return mRgb.getG();
}

unsigned char *Rgba::getB()
{
    return mRgb.getB();
}

unsigned char *Rgba::getA()
{
    return &mA;
}
