#ifndef JPEG_H
#define JPEG_H

#include "image.h"

class Jpeg : public ipl::Image
{
public:
    Jpeg(const std::string &pAbsolutePath);
    ~Jpeg();

    // Image interface
protected:
    bool write(const std::string &pAbsoluteFolderPath, const std::string& pFileName) override;
};

#endif // JPEG_H
