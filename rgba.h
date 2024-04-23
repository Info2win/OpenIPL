#ifndef RGBA_H
#define RGBA_H

#include "rgb.h"
#include "pixel.h"

class Rgba : public Pixel
{
public:
    Rgba(unsigned char pR, unsigned char pG, unsigned char pB, unsigned char pA);
    // Pixel interface
    unsigned char* getR() override;
    unsigned char* getG() override;
    unsigned char* getB() override;
    unsigned char* getA() override;

private:
    unsigned char mR,mG,mB,mA;
    // Pixel interface
public:
    void setR(unsigned char *pR) override;
    void setG(unsigned char *pG) override;
    void setB(unsigned char *pB) override;
    void setA(unsigned char *pA) override;
};

#endif // RGBA_H
