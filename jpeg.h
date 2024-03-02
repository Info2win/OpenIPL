#ifndef JPEG_H
#define JPEG_H

#include "image.h"

class Jpeg : public ipl::Image
{
public:
    Jpeg(const char* pAbsolutePath);
    ~Jpeg();

    // Image interface
protected:
    bool write(const char* pAbsoluteFolderPath, const char* pFileName) override;
};

#endif // JPEG_H
