#pragma once

class Scene
{
private:
    int width, height;
    int maxDepth;
    Vec3 lookfrom, lokat, up;
    double fovx, fovy;
public:
    void setSize(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    void setMaxDepth(int maxDepth)
    {
        this->maxDepth = maxDepth;
    }

    void setCamera(const Vec3& lookfrom, const Vec3& loookat, const Vec3& up, double fovx, double fovy)
    {
        this->lookfrom = lookfrom;
        this->lookat = lookat;
        this->up = up;
        this->fovx = fovx;
        this->fovy = fovy;
    }

    void draw();
};
