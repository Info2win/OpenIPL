#ifndef RGB_H
#define RGB_H

#include "pixel.h"

class Rgb : public Pixel
{
public:
    Rgb(unsigned char& pR, unsigned char& pG, unsigned char& pB);
    // Pixel interface
    unsigned char* getR()  override;
    unsigned char* getG()  override;
    unsigned char* getB()  override;
private:
    unsigned char mR;
    unsigned char mG;
    unsigned char mB;

    // Pixel interface
public:
    void setR(unsigned char *pR) override;
    void setG(unsigned char *pG) override;
    void setB(unsigned char *pB) override;
};

#endif // RGB_H
