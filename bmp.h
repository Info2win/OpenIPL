#ifndef BMP_H
#define BMP_H

#include "image.h"

class Bmp : public ipl::Image
{
public:
    Bmp(const char* pAbsolutePath);
    ~Bmp();

    // Image interface
public:
    bool write(const char *pAbsoluteFolderPath, const char *pFileName) override;
};

#endif // BMP_H
