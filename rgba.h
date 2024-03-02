#ifndef RGBA_H
#define RGBA_H

#include "rgb.h"
#include "pixel.h"

class Rgba : public Pixel
{
public:
    Rgba(Rgb pRgb, unsigned char pA);
    Rgba(unsigned char pR, unsigned char pG, unsigned char pB, unsigned char pA);

    Rgb* getRgb();
    // Pixel interface
    unsigned char* getR() override;
    unsigned char* getG() override;
    unsigned char* getB() override;
    unsigned char* getA() override;

private:
    Rgb mRgb;
    unsigned char mA;
};

#endif // RGBA_H
