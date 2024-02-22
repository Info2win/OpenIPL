#ifndef PNG_H
#define PNG_H

#include "image.h"

/**
 * @brief The Png class
 */
class Png : public ipl::Image
{
public:
    Png(const std::string &pAbsolutePath);
    ~Png();
    // Image interface
protected:
    bool write(const std::string &pAbsoluteFolderPath, const std::string& pFileName) override;
};

#endif // PNG_H
