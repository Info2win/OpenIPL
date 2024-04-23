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


void Rgb::setR(unsigned char *pR)
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

void Rgb::setG(unsigned char *pG)
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

void Rgb::setB(unsigned char *pB)
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
