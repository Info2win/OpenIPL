#include "bmp.h"
#include <iostream>

// STB Headers
#include "third_party/stb/stb_image_write.h"

Bmp::Bmp(const char *pAbsolutePath) : ipl::Image(pAbsolutePath)
{
    std::cout << "Constructed bmp"<< std::endl;
}

Bmp::~Bmp()
{
    std::cout << "Deconstructed bmp"<< std::endl;
}


bool Bmp::write(const char *pAbsoluteFolderPath, const char *pFileName)
{
    try
    {
        std::string tempAbsoluteFolderPath = std::string(pAbsoluteFolderPath);
        std::string tempFileName = std::string(pFileName);
        std::string tempAbsoluteFilePath = tempAbsoluteFolderPath + "/" + tempFileName;

        int isWritten;
        isWritten = stbi_write_bmp(tempAbsoluteFilePath.c_str(),mWidth, mHeight, mChannelCount,this->toUnsignedCharArray());
        if(!isWritten)
        {
            std::cerr << "Could not write!"<< std::endl;
            return false;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return false;
    }
    return true;

}
