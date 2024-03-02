#include "jpeg.h"
#include <iostream>

// STB Headers
#include "third_party/stb/stb_image_write.h"

Jpeg::Jpeg(const char* pAbsolutePath) : ipl::Image(pAbsolutePath)
{
    std::cout << "Constructed jpeg"<< std::endl;
}

Jpeg::~Jpeg()
{
    std::cout << "Deconstructed jpeg"<< std::endl;
}

bool Jpeg::write(const char* pAbsoluteFolderPath, const char* pFileName)
{
    std::string tempAbsoluteFolderPath = std::string(pAbsoluteFolderPath);
    std::string tempFileName = std::string(pFileName);
    std::string tempAbsoluteFilePath = tempAbsoluteFolderPath + "/" + tempFileName;

    int isWritten;
    isWritten = stbi_write_jpg(tempAbsoluteFilePath.c_str(),mWidth,mHeight,mChannelCount,this->toUnsignedCharArray(), 100);
    if(!isWritten)
    {
        std::cerr << "Could not write!"<< std::endl;
        return false;
    }
    return true;
}
