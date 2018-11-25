#pragma once

#include "General.h"

/**
 * Undefined behaviour
 *  height or width is non-positive
 */
struct Sampler
{
private:
    // Members
    int width, height;
    int index;

public:
    // Constructor
    Sampler(): width(100), height(100), index(0) {}

    // Setters and getters
    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;
        this->index = 0;
    }

    // Operations
    bool generateSample(glm::vec2& sample)
    {
        if (index == width*height) return false;
        sample[0] = .5f+index%width;
        sample[1] = .5f+index/width;
        index++;
        return true;
    }
};
