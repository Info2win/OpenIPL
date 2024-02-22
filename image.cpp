#include "image.h"
#include "png.h"
#include "jpeg.h"
#include <iostream>

ipl::Image::Image()
{
    std::cout << "Constructor of Image is called" << std::endl;
}
ipl::Image::~Image()
{
    std::cout << "Deconstructor of Image is called" << std::endl;
}

ipl::Image *ipl::Image::read(const std::string &pAbsolutePath)
{
        // find image type

        std::size_t dotPos = pAbsolutePath.find_last_of('.');
        std::string imageType;
        if(dotPos != std::string::npos)
        {
            imageType = pAbsolutePath.substr(dotPos+1);
        }
        // construct and return the image according to type
        if(imageType == "png")
        {
            return new Png(pAbsolutePath);
        }
        else if(imageType == "jpeg")
        {
            return new Jpeg(pAbsolutePath);
        }
        else
        {
            std::cerr<< "Image type is not supported yet!";
            std::abort();
            return nullptr;
        }

}


