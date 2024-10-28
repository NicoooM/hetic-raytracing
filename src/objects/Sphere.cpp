#include <iostream>
#include "Sphere.hpp"
#include "../raymath/Vector3.hpp"

Sphere::Sphere() : center(Vector3()), r(0), color(Color())
{
}

Sphere::Sphere(Vector3 iCenter, float iR, Color iColor) : center(iCenter), r(iR), color(iColor)
{
}

Sphere::~Sphere()
{
}

float Sphere::X() const
{
    return center.X();
}

float Sphere::Y() const
{
    return center.Y();
}

float Sphere::Z() const
{
    return center.Z();
}

float Sphere::R() const
{
    return r;
}

Color Sphere::GetColor() const // Renamed method
{
    return color;
}

Vector3 Sphere::GetCenter() const // Renamed method
{
    return center;
}

Sphere &Sphere::operator=(Sphere const &sphere)
{
    center = sphere.center;
    r = sphere.r;
    color = sphere.color;
    return *this;
}

std::ostream &operator<<(std::ostream &_stream, Sphere const &sphere)
{
    return _stream << "Sphere(" << sphere.center << "," << sphere.r << "," << sphere.color << ")";
}