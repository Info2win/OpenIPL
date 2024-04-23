#include "rgba.h"


Rgba::Rgba(unsigned char pR, unsigned char pG, unsigned char pB, unsigned char pA)
{
    if(pR>255)
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
    if(pG>255)
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
    if(pB>255)
    {
        mB = 255;
    }
    else if(pB < 0)
    {
        mB = 0;
    }
    else
    {
        mB = pB;
    }
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


unsigned char *Rgba::getR()
{
    return &mR;
}

unsigned char *Rgba::getG()
{
    return &mG;
}

unsigned char *Rgba::getB()
{
    return &mB;
}

unsigned char *Rgba::getA()
{
    return &mA;
}

void Rgba::setR(unsigned char *pR)
{
    if(*pR > 255)
    {
        *pR = 255;
    }
    else if (*pR < 0)
    {
        *pR = 0;
    }
    else
    {
        mR = *pR;
    }
}

void Rgba::setG(unsigned char *pG)
{
    if(*pG > 255)
    {
        *pG = 255;
    }
    else if (*pG < 0)
    {
        *pG = 0;
    }
    else
    {
        mG = *pG;
    }
}

void Rgba::setB(unsigned char *pB)
{
    if(*pB > 255)
    {
        *pB = 255;
    }
    else if (*pB < 0)
    {
        *pB = 0;
    }
    else
    {
        mB = *pB;
    }
}

void Rgba::setA(unsigned char *pA)
{
    if(*pA > 255)
    {
        *pA = 255;
    }
    else if (*pA < 0)
    {
        *pA = 0;
    }
    else
    {
        mA = *pA;
    }
}
