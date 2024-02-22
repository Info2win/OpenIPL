#include "jpeg.h"
#include <iostream>
Jpeg::Jpeg(const std::string &pAbsolutePath)
{
    std::cout << "Constructed jpeg"<< std::endl;
}

Jpeg::~Jpeg()
{
    std::cout << "Deconstructed jpeg"<< std::endl;
}

bool Jpeg::write(const std::string &pAbsoluteFolderPath)
{
    return false;
}
