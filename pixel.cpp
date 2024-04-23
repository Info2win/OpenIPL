#include "pixel.h"

Pixel::~Pixel()
{

}

unsigned char *Pixel::getR()
{
    return nullptr;
}

unsigned char *Pixel::getG()
{
    return nullptr;
}

unsigned char *Pixel::getB()
{
    return nullptr;
}

unsigned char *Pixel::getA()
{
    return nullptr;
}

unsigned char *Pixel::getIntensity()
{
    return nullptr;
}

void Pixel::setR(unsigned char *pR)
{
    // Pixel is an interface, implementation is done in actual classes such as rgb,rgba
}

void Pixel::setG(unsigned char *pG)
{
    // Pixel is an interface, implementation is done in actual classes such as rgb,rgba
}

void Pixel::setB(unsigned char *pB)
{
    // Pixel is an interface, implementation is done in actual classes such as rgb,rgba
}

void Pixel::setA(unsigned char *pA)
{
    // Pixel is an interface, implementation is done in actual classes such as rgba
}

void Pixel::setIntensity(unsigned char *pIntensity)
{
    // Pixel is an interface, implementation is done in actual classes such as grayscale
}
