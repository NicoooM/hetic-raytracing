#include <iostream>
#include "Vector3.hpp"
#include <cmath>


Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float iX, float iY, float iZ) : x(iX), y(iY), z(iZ)
{
}

Vector3::~Vector3()
{
}

float Vector3::X() const
{
    return x;
}

float Vector3::Y() const
{
    return y;
}

float Vector3::Z() const
{
    return z;
}

Vector3 Vector3::Normalize() const
{
    float length = sqrt(x * x + y * y + z * z);
    return Vector3(x / length, y / length, z / length);
}

float Vector3::DotProduct(Vector3 const &vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::Projection(Vector3 const &vec) const
{
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

// Vector3 Vector3::Reflect(Vector3 const &normal) const
// {
//     Vector3 proj = this->Projection(normal);
//     proj = proj * -2;
//     Vector3 reflectDir = *this + proj;
//     return ;
// }


std::ostream &operator<<(std::ostream &_stream, Vector3 const &vec)
{
    return _stream << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
}