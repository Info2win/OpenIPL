#ifndef PIXEL_H
#define PIXEL_H

#include "OpenIPL_global.h"

class OPENIPL_API Pixel
{
public:
    virtual ~Pixel();
    /**
     * @brief getR
     * @return Returns a pointer to Red value of the pixel, if it is GrayScale returns nullptr
     */
    virtual unsigned char* getR();
    /**
     * @brief getG
     * @return Returns a pointer to Green value of the pixel, if it is GrayScale returns nullptr
     */
    virtual unsigned char* getG();
    /**
     * @brief getB
     * @return Returns a pointer to Blue value of the pixel, if it is GrayScale returns nullptr
     */
    virtual unsigned char* getB();
    /**
     * @brief getA
     * @return Returns a pointer to Alpha value of the pixel, if it is GrayScale or RGB returns nullptr
     */
    virtual unsigned char* getA();
    /**
     * @brief getIntensity
     * @return Returns a pointer to Instensity value of the pixel, if it is not GrayScale returns nullptr
     */
    virtual unsigned char* getIntensity();
};

#endif // PIXEL_H
