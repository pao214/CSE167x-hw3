#pragma once

struct Vector;

struct Point
{
    // Members
    float x, y, z;

    // Constructors
    Point(float x, float y, float z): x(x), y(y), z(z) {}

    // Operations
    friend Point operator+(const Point& op1, const Vector& op2);
    friend Point operator-(const Point& op1, const Vector& op2);
    friend Vector operator-(const Point& op1, const Point& op2);
};

struct Vector
{
    // Members
    float x, y, z;

    // Constructor
    Vector(float x, float y, float z): x(x), y(y), z(z) {}

    // Operations
    friend Vector operator+(const Vector& op1, const Vector& op2);
    friend Vector operator-(const Vector& op1, const Vector& op2);
    friend Vector operator*(const float op1, const Vector& op2);
    friend Vector operator*(const Vector& op1, const float op2);
    friend Vector operator/(const Vector& op1, const Vector& op2);
};

// Vector operations
inline Vector operator+(const Vector& op1, const Vector& op2)
{
    return Vector(op1.x+op2.x, op1.y+op2.y, op1.z+op2.z);
}

inline Vector operator-(const Vector& op1, const Vector& op2)
{
    return Vector(op1.x-op2.x, op1.y-op2.y, op1.z-op2.z);
}

inline Vector operator*(const float op1, const Vector& op2)
{
    return Vector(op1*op2.x, op1*op2.y, op1*op2.z);
}

inline Vector operator*(const Vector& op1, const float op2)
{
    return Vector(op1.x*op2, op1.y*op2, op1.z*op2);
}

inline Vector operator/(const Vector& op1, const float op2)
{
    return Vector(op1.x/op2, op1.y/op2, op1.z/op2);
}

// Point operations
inline Point operator+(const Point& op1, const Vector& op2)
{
    return Point(op1.x+op2.x, op1.y+op2.y, op1.z+op2.z);
}

inline Point operator-(const Point& op1, const Vector& op2)
{
    return Point(op1.x-op2.x, op1.y-op2.y, op1.z-op2.z);
}

inline Vector operator-(const Point& op1, const Point& op2)
{
    return Vector(op1.x-op2.x, op1.y-op2.y, op1.z-op2.z);
}
