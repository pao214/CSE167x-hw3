#pragma once

#include "General.h"
#include "FreeImage.h"

/**
 * Undefined behaviour
 *  x < 0 || x >= width || y <0 || y >= height
 */
struct Film
{
private:
    // Members
    int width, height;
    std::string outputFilename;
    std::vector<uint8_t> pixels;

public:
    // Constructor
    Film(): width(160), height(120), outputFilename("raytrace.png") {}

    // Setters and getters
    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;
        pixels.resize(width*height*3);
    }

    void setOutputFilename(const std::string& outputFilename)
    {
        this->outputFilename = outputFilename;
    }

    // Operations
    void commit(int x, int y, const glm::vec3& color)
    {
        int index = x+y*width;
        auto convertRange = [] (float f) { return static_cast<uint8_t>(f == 1.0f ? 255 : f*256.0f); };
        pixels[3*index+2] = convertRange(color[0]);
        pixels[3*index+1] = convertRange(color[1]);
        pixels[3*index] = convertRange(color[2]);
        std::cerr << (100.*index)/(width*height) << "% done\r";
    }

    void saveImage()
    {
        // Save screenshot to file.
        FreeImage_Initialise();
        FIBITMAP *image = FreeImage_ConvertFromRawBits(&pixels[0], width, height, width*3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
        std::cout << "Saving image: " << outputFilename << std::endl;
        FreeImage_Save(FIF_PNG, image, outputFilename.c_str(), 0);
        FreeImage_DeInitialise();
    }
};
