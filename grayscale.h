#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include "pixel.h"

class GrayScale : public Pixel
{
public:
    GrayScale(unsigned char& pIntensity);

    // Pixel interface
    unsigned char *getIntensity() override;

private:
    unsigned char mIntensity;


    // Pixel interface
public:
    void setIntensity(unsigned char *pIntensity) override;
};

#endif // GRAYSCALE_H
