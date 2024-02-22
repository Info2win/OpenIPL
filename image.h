#ifndef IMAGE_H
#define IMAGE_H


#include "OpenIPL_global.h"

#include <string>

namespace ipl{

/**
 * @brief The Image class initiates a god object for you to do your all image processing operations.
 *        Simply, start with read method to read an image from disk to memory.
 *        Then, call other methods that you wish.
 *        Lastly, you can write to disk from memory with write method.
 */
class OPENIPL_API Image
{
public:
    /**
     * @brief Reads an image from the disk to memory.
     * @param pAbsolutePath is the absoulte path to the image.
     * @return Returns an pointer to Image object.
     */
    static Image* read(const std::string& pAbsolutePath);

    /**
     * @brief Writes an image from the memory to disk.
     * @param pAbsoluteFolderPath is the absolute path to the folder where you want to write your image.
     * @param pFileName is the name of the image that is going to be written.
     * @return Returns true if the image is successfully written, otherwise false.
     */
    virtual bool write(const std::string& pAbsoluteFolderPath, const std::string& pFileName) = 0;
protected:
    Image();
    virtual ~Image();
};

}

#endif // IMAGE_H
