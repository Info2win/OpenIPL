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



