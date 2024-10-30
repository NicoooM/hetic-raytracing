#include <iostream>
#include "Vector3.hpp"
#include <cmath>

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) 
{
}

Vector3::~Vector3()
{
}

float Vector3::get_x() const
{
    return x;
}

float Vector3::get_y() const
{
    return y;
}

float Vector3::get_z() const
{
    return z;
}

Vector3 Vector3::normalize() const
{
    float length = sqrt(x * x + y * y + z * z);
    return Vector3(x / length, y / length, z / length);
}

float Vector3::dot_product(Vector3 const &vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}

float Vector3::pythagorean() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator+(Vector3 const &vec) const
{
    return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(Vector3 const &vec) const
{
    return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 &Vector3::operator=(Vector3 const &vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

Vector3 Vector3::operator*(float const &val) const
{
    return Vector3(x * val, y * val, z * val);
}

std::ostream &operator<<(std::ostream &stream, Vector3 const &vec)
{
    return stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
}