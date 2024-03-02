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

};

#endif // GRAYSCALE_H
