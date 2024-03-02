#ifndef PNG_H
#define PNG_H

#include "image.h"

/**
 * @brief The Png class
 */
class Png : public ipl::Image
{
public:
    Png(const char* pAbsolutePath);
    ~Png();
    // Image interface
private:
    bool write(const char* pAbsoluteFolderPath, const char* pFileName) override;
};

#endif // PNG_H
