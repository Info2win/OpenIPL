#ifndef IMAGE_H
#define IMAGE_H

// OpenIPL headers
#include "OpenIPL_global.h"
#include "pixel.h"

// STL headers
#include <vector>
#include <string>
#include <thread>
#include <mutex>

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
     * This a thread safe method.
     * @param pAbsolutePath is the absoulte path to the image.
     * @return Returns a pointer to Image object if successfully read, otherwise returns nullptr.
     */
    static Image* read(const char* pAbsolutePath);

    /**
     * @brief Writes an image from the memory to disk.
     * This a thread safe method.
     * @param pAbsoluteFolderPath is the absolute path to the folder where you want to write your image.
     * @param pFileName is the name of the image that is going to be written.
     * @return Returns true if the image is successfully written, otherwise false.
     */
    virtual bool write(const char* pAbsoluteFolderPath, const char* pFileName) = 0;

    //destructor
    virtual ~Image();   

protected:
    // consturctors and destructors
    Image(const char* pAbsolutePath);
    //member variables
    int mWidth;
    int mHeight;
    int mChannelCount;
    std::vector<std::vector<Pixel*>> mImageMatrix;
    unsigned char* toUnsignedCharArray();
private:
    void setImageMatrix(unsigned char* pImage,const int& pStartRow, const int& pEndRow, std::mutex& pMutex);
    void setUnsignedCharArray(unsigned char* pResult,const int& pStartRow, const int& pEndRow, std::mutex& pMutex);
    std::mutex mMutex;

};

}

#endif // IMAGE_H
