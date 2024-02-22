#include "png.h"
#include <iostream>
Png::Png(const std::string& pAbsolutePath)
{
    std::cout << "constructed png"<< std::endl;
}

Png::~Png()
{
    std::cout << "deconstructed png"<< std::endl;
}

bool Png::write(const std::string &pAbsoluteFolderPath)
{
    return false;
}
