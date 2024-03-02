#include "png.h"
#include <iostream>


// STB Headers
#include "third_party/stb/stb_image_write.h"



Png::Png(const char* pAbsolutePath) : ipl::Image(pAbsolutePath)
{
    std::cout << "constructed png"<< std::endl;
}

Png::~Png()
{
    std::cout << "deconstructed png"<< std::endl;
}

bool Png::write(const char* pAbsoluteFolderPath, const char* pFileName)
{
    std::string tempAbsoluteFolderPath = std::string(pAbsoluteFolderPath);
    std::string tempFileName = std::string(pFileName);
    std::string tempAbsoluteFilePath = tempAbsoluteFolderPath + "/" + tempFileName;

    int isWritten;
    isWritten = stbi_write_png(tempAbsoluteFilePath.c_str(),mWidth, mHeight, mChannelCount,this->toUnsignedCharArray(), mWidth * mChannelCount);
    if(!isWritten)
    {
        std::cerr << "Could not write!"<< std::endl;
        return false;
    }
    return true;
}
