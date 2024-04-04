#include "image.h"
#include "png.h"
#include "jpeg.h"
#include "rgba.h"
#include "rgb.h"
#include "grayscale.h"

// STL headers
#include <iostream>


// STB headers
#include "third_party/stb/stb_image.h"

ipl::Image::Image(const char* pAbsolutePath)
{
    std::cout << "Constructor of Image is called" << std::endl;

    // Load the image with the same channel count by passing 0 to desired_channels (last parameter)
    unsigned char* tempImage = stbi_load(pAbsolutePath,&mWidth,&mHeight,&mChannelCount,0);
    //Check if loaded
    if(!tempImage)
    {
        std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        std::abort();
    }
    // Convert and store the image as unsigned int matrix in parallel
    // Allocate memory for pixels in matrix
    mImageMatrix.resize(mHeight);
    for(int i = 0; i<mHeight; ++i)
    {
        mImageMatrix[i].resize(mWidth);
    }

    // Divide the image rows among the threads
    unsigned int threadsCount = std::thread::hardware_concurrency();// Get avaiable thread count
    std::vector<std::thread> threads;
    int rowsPerThread = mHeight / threadsCount;
    int startRow = 0;
    int endRow=0;

    for(unsigned int i=0; i<threadsCount; ++i)
    {
        if(i == threadsCount - 1)
        {
            endRow = mHeight;
        }
        else
        {
            endRow = startRow + rowsPerThread;
        }
        threads.emplace_back(&Image::setImageMatrix,this,tempImage,startRow,endRow, std::ref(mMutex));
        startRow += rowsPerThread;
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    stbi_image_free(tempImage);
}


ipl::Image::~Image()
{
    std::cout << "Deconstructor of Image is called" << std::endl;

    if(mImageMatrix.data() && mImageMatrix.data()->data()) // if mImageMatrix is filled, clear the pointers
    {
        for(int i=0; i<mImageMatrix.size(); ++i)
        {
            for(int k=0; k<mImageMatrix[0].size(); ++k)
            {
                delete mImageMatrix[i][k];
            }
        }
    }

}


bool ipl::Image::resize(const int& pNewWidth, const int& pNewHeight)
{
    try
    {
        std::vector<std::vector<Pixel*>> outputMatrix(pNewHeight);
        for(int i=0; i< pNewHeight; ++i)
        {
            outputMatrix.resize(pNewWidth);
        }
        int oldWidth = mImageMatrix[0].size();
        int oldHeight = mImageMatrix.size();

        float widthRatio = (float)(oldWidth-1) / (pNewWidth - 1);
        float heightRatio = (float)(oldHeight -1) / (pNewHeight - 1);


        for(int height =0; height<pNewHeight; ++height)
        {
            for(int width=0; width<pNewWidth; ++width)
            {
                // Coordinates in the original image
                float width_src = width * widthRatio;
                float height_src = height * heightRatio;

                // Find the integer part of coordinates

                int width_int = (int)width_src;
                int height_int = (int)height_src;

                // Fractional parts of the coordinates

                float width_diff = width_src - width_int;
                float height_diff = height_src - height_int;

                unsigned char newRValue;
                unsigned char newGValue;
                unsigned char newBValue;
                unsigned char newAValue;
                unsigned char newGrayScaleValue;
                Pixel* pixel = nullptr;

                // Bilinear interpolation
                if(height_int < mHeight -1 && width_int < mWidth -1 )
                {
                    if(mChannelCount >= 3) // RGB or RGBA
                    {

                        newRValue =
                                (1 - width_diff) * (1 - height_diff) * *(mImageMatrix[height_int][width_int]->getR() )+
                                width_diff * (1 - height_diff) * *(mImageMatrix[height_int][width_int + 1]->getR() )+
                                (1 - width_diff) * height_diff * *(mImageMatrix[height_int + 1] [width_int]->getR()) +
                                width_diff * height_diff * *(mImageMatrix[height_int + 1] [width_int + 1]->getR());
                        newGValue =
                                (1 - width_diff) * (1 - height_diff) * *(mImageMatrix[height_int][width_int]->getG() )+
                                width_diff * (1 - height_diff) * *(mImageMatrix[height_int][width_int + 1]->getG() )+
                                (1 - width_diff) * height_diff * *(mImageMatrix[height_int + 1] [width_int]->getG()) +
                                width_diff * height_diff * *(mImageMatrix[height_int + 1] [width_int + 1]->getG());
                        newBValue =
                                (1 - width_diff) * (1 - height_diff) * *(mImageMatrix[height_int][width_int]->getB() )+
                                width_diff * (1 - height_diff) * *(mImageMatrix[height_int][width_int + 1]->getB() )+
                                (1 - width_diff) * height_diff * *(mImageMatrix[height_int + 1] [width_int]->getB()) +
                                width_diff * height_diff * *(mImageMatrix[height_int + 1] [width_int + 1]->getB());

                        if(mChannelCount == 3) // RGB
                        {
                            pixel = new Rgb(newRValue,newGValue,newBValue);

                        }
                    }
                    if(mChannelCount == 4) // RGBA
                    {
                        newAValue =
                                (1 - width_diff) * (1 - height_diff) * *(mImageMatrix[height_int][width_int]->getA() )+
                                width_diff * (1 - height_diff) * *(mImageMatrix[height_int][width_int + 1]->getA() )+
                                (1 - width_diff) * height_diff * *(mImageMatrix[height_int + 1] [width_int]->getA()) +
                                width_diff * height_diff * *(mImageMatrix[height_int + 1] [width_int + 1]->getA());
                        pixel = new Rgba(newRValue,newGValue,newBValue,newAValue);
                    }
                    if(mChannelCount == 1) // GrayScale
                    {
                        newGrayScaleValue =
                                (1 - width_diff) * (1 - height_diff) * *(mImageMatrix[height_int][width_int]->getIntensity() )+
                                width_diff * (1 - height_diff) * *(mImageMatrix[height_int][width_int + 1]->getIntensity() )+
                                (1 - width_diff) * height_diff * *(mImageMatrix[height_int + 1] [width_int]->getIntensity() ) +
                                width_diff * height_diff * *(mImageMatrix[height_int + 1] [width_int + 1]->getIntensity() );
                        pixel = new GrayScale(newGrayScaleValue);
                    }
                    outputMatrix[height].push_back(pixel);
                }
                else // if right or bottom edge output pixel is same as one pixel before it
                {
                    if(height_int == mHeight -1 && width_int == mWidth -1)
                    {
                        outputMatrix[height].push_back(outputMatrix[height-1][width-1]);
                    }
                    else if(height_int == mHeight -1 && width_int < mWidth -1)
                    {
                        outputMatrix[height].push_back(outputMatrix[height-1][width]);
                    }
                    else if(height_int < mHeight -1 && width_int == mWidth -1)
                    {
                        outputMatrix[height].push_back(outputMatrix[height][width-1]);
                    }
                }

            }
        }
        mImageMatrix.resize(pNewHeight);
        for(int i=0; i< pNewHeight; ++i)
        {
            mImageMatrix[i].resize(pNewWidth);
        }
        mImageMatrix = outputMatrix;

    }
    catch (const std::exception& e)
    {
       std::cerr << "Exception caught: " << e.what() << std::endl;
       return false;
    }

    mHeight = pNewHeight;
    mWidth = pNewWidth;

    return true;
}

bool ipl::Image::toGrayScale()
{
    try
    {
       unsigned char intensity=0;
       if(mChannelCount >= 3) // RGB or RGBA
       {
            for(int height=0; height<mHeight; ++height)
            {
                for(int width=0; width< mWidth; ++width)
                {
                    Pixel* currentPixel = mImageMatrix[height][width];
                        // Convert to grayscale using luminosity method
                    intensity = static_cast<unsigned char>(0.21f * *currentPixel->getR() +
                                                           0.72f * *currentPixel->getG() + 0.07f * *currentPixel->getB());
                    if(mChannelCount == 4) // RGBA
                    {
                        intensity *= *currentPixel->getA();
                    }
                    mImageMatrix[height][width] = new GrayScale(intensity);
                    mChannelCount = 1;
                }
            }

       }
       if(mChannelCount == 1)// Already GrayScale
       {
            return true;
       }
    }
    catch (const std::exception& e)
    {
       std::cerr << "Exception caught: " << e.what() << std::endl;
       return false;
    }

    return true;

}

bool ipl::Image::toBinary(const int &pThreshold)
{
    try
    {
       unsigned char intensity=0;
       if(mChannelCount >= 3) // RGB or RGBA
       {
            for(int height=0; height<mHeight; ++height)
            {
                for(int width=0; width< mWidth; ++width)
                {
                    Pixel* currentPixel = mImageMatrix[height][width];
                        // Convert to grayscale using luminosity method
                    intensity = static_cast<unsigned char>(0.21f * *currentPixel->getR() +
                                                           0.72f * *currentPixel->getG() + 0.07f * *currentPixel->getB());
                    if(mChannelCount == 4) // RGBA
                    {
                        intensity *= *currentPixel->getA();
                    }
                    if(intensity >= pThreshold)
                    {
                        intensity = 255;
                    }
                    else
                    {
                        intensity = 0;
                    }
                    mImageMatrix[height][width] = new GrayScale(intensity);
                    mChannelCount = 1;
                }
            }

       }
       if(mChannelCount == 1)// Already GrayScale
       {
            return true;
       }
    }
    catch (const std::exception& e)
    {
       std::cerr << "Exception caught: " << e.what() << std::endl;
       return false;
    }

    return true;
}

bool ipl::Image::crop(const int &pStartHeight, const int &pEndHight, const int &pStartWidth, const int &pEndWidth)
{
    int heightLength = pEndHight - pStartHeight;
    int widthLength = pEndWidth - pStartWidth;
    std::vector<std::vector<Pixel*>> outputMatrix(heightLength);

    try
    {
       int i =0;
       for(int height=pStartHeight; height<pEndHight; ++height, ++i)
       {
            for(int width=pStartWidth; width < pEndWidth; ++width)
            {
                outputMatrix[i].push_back(mImageMatrix[height][width]);
            }
       }

       mImageMatrix.resize(heightLength);
       for(int i=0; i<heightLength; ++i)
       {
            mImageMatrix.resize(widthLength);
       }
       mImageMatrix = outputMatrix;

    }
    catch (const std::exception& e)
    {
       std::cerr << "Exception caught: " << e.what() << std::endl;
       return false;
    }

    mHeight = heightLength;
    mWidth = widthLength;
    return true;
}

bool ipl::Image::append(const Image *pImage, const int &pStartHeight, const int &pStartWidth)
{
    int newHeight = pImage->getHeight() + pStartHeight;
    int newWidth = pImage->getWidth() + pStartWidth;
    try
    {
        if(newHeight < mHeight)
        {
           newHeight = mHeight;
        }
        if(newWidth < mWidth)
        {
            newWidth = mWidth;
        }
        Pixel* pixel = nullptr;
        if(mChannelCount == 4)
        {
            unsigned char r,g,b,a = '0';
            pixel = new Rgba(r,g,b,a);
        }
        else if (mChannelCount == 3)
        {
            unsigned char r,g,b = '0';
            pixel = new Rgb(r,g,b);
        }
        else
        {
            unsigned char intensity ='0';
            pixel = new GrayScale(intensity);
        }
        // resize the width of the original image according to new width, with default black pixel
        for(int height = 0; height < mHeight; ++height)
        {
            mImageMatrix[height].resize(newWidth,pixel);
        }
        // resize the height of the original image according to new height, with default black pixel
        for(int height = mHeight; height < newHeight; ++height)
        {
            mImageMatrix.resize(newHeight,std::vector<Pixel*>(newWidth,pixel));
        }
        //append the image

        for(int height = 0; height<pImage->getHeight(); ++height)
        {
            for(int width = 0; width <pImage->getWidth(); ++width)
            {
                mImageMatrix[height+pStartHeight][width+pStartWidth] = pImage->mImageMatrix[height][width];
            }
        }
    }
    catch (const std::exception& e)
    {
       std::cerr << "Exception caught: " << e.what() << std::endl;
       return false;
    }

    mHeight = newHeight;
    mWidth = newWidth;

    return true;
}


void ipl::Image::setImageMatrix(unsigned char *pImage, const int &pStartRow, const int &pEndRow, std::mutex &pMutex)
{
    pMutex.lock();

    Pixel* pixel = nullptr;
    int tRow = pStartRow;
    int tColumn = 0;
    pImage = pImage + pStartRow * mWidth * mChannelCount;
    for(int i=0; i< (pEndRow - pStartRow) * mWidth * mChannelCount;)
    {
        if(mChannelCount == 4) // rgba
        {
            pixel = new Rgba(*(pImage + i),*(pImage + i + 1 ),*(pImage + i + 2), *(pImage + i + 3));
            i += 4;
        }
        else if(mChannelCount == 3) // rgb
        {
            pixel = new Rgb(*(pImage + i),*(pImage + i + 1 ),*(pImage + i + 2));
            i += 3;
        }
        else // GrayScale
        {
            pixel = new GrayScale(*(pImage + i));
            i += 1;
        }
        mImageMatrix[tRow][tColumn] = pixel;
        ++tColumn;
        if(( i % (mWidth * mChannelCount)) == 0)
        {
            ++tRow;
            tColumn = 0;
        }
    }

    pMutex.unlock();
}

unsigned char* ipl::Image::toUnsignedCharArray()
{
    unsigned char* result= new unsigned char[mWidth * mChannelCount * mHeight];

    // Convert and store the image as unsigned int matrix in parallel
    unsigned int threadsCount = std::thread::hardware_concurrency();// Get avaiable thread count

    // Divide the image rows among the threads
    std::vector<std::thread> threads;
    int rowsPerThread = mHeight / threadsCount;
    int startRow = 0;
    int endRow=0;

    for(unsigned int i=0; i<threadsCount; ++i)
    {
        if(i == threadsCount - 1)
        {
            endRow = mHeight;
        }
        else
        {
            endRow = startRow + rowsPerThread;
        }
        threads.emplace_back(&Image::setUnsignedCharArray,this,result,startRow,endRow,std::ref(mMutex));
        startRow += rowsPerThread;
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    return result;

}

void ipl::Image::setUnsignedCharArray(unsigned char* pResult, const int &pStartRow, const int &pEndRow, std::mutex &pMutex)
{
    pMutex.lock();

    Pixel* pixel = nullptr;
    int tRow = pStartRow;
    int tColumn = 0;

    pResult = pResult + pStartRow * mWidth * mChannelCount;

    for(int i=0; i< (pEndRow - pStartRow) * mWidth * mChannelCount;)
    {
        if(mChannelCount == 4) // rgba
        {
            pixel = mImageMatrix[tRow][tColumn];
            *(pResult + i) = *(pixel->getR());
            *(pResult + i + 1) = *(pixel->getG());
            *(pResult + i + 2) = *(pixel->getB());
            *(pResult + i + 3) = *(pixel->getA());
            i += 4;
        }
        else if(mChannelCount == 3) // rgb
        {
            pixel = mImageMatrix[tRow][tColumn];
            *(pResult + i) = *(pixel->getR());
            *(pResult + i + 1) = *(pixel->getG());
            *(pResult + i + 2) = *(pixel->getB());
            i += 3;
        }
        else // mChannelCount is 1 and image is GrayScale
        {
            pixel = mImageMatrix[tRow][tColumn];
            *(pResult + i) = *(pixel->getIntensity());
            i += 1;
        }
        ++tColumn;
        if(( i % (mWidth * mChannelCount)) == 0)
        {
            ++tRow;
            tColumn = 0;
        }
    }

    pMutex.unlock();
}

ipl::Image *ipl::Image::read(const char* pAbsolutePath)
{
        // find image type
        std::string* tempAbsolutePath = new std::string(pAbsolutePath);
        std::size_t dotPos = tempAbsolutePath->find_last_of('.');
        std::string imageType;
        if(dotPos != std::string::npos)
        {
        imageType = tempAbsolutePath->substr(dotPos+1);
        }
        delete tempAbsolutePath;
        // construct and return the image according to type
        if(imageType == "png")
        {
            return new Png(pAbsolutePath);
        }
        else if(imageType == "jpeg" || imageType == "jpg")
        {

            return new Jpeg(pAbsolutePath);

        }
        else
        {
            std::cerr<< "Image type is not supported yet!";
            return nullptr;
        }

}





namespace ipl {

int Image::getHeight() const
{
    return mHeight;
}

int Image::getWidth() const
{
    return mWidth;
}

}
