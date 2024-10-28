#include <iostream>
#include "Sphere.hpp"
#include "../raymath/Vector3.hpp"

Sphere::Sphere() : center(vector3()), r(0), color(Color())
{
}

Sphere::Sphere(vector3 iCenter, float iR, Color iColor) : center(iCenter), r(iR), color(iColor)
{
}

Sphere::~Sphere()
{
}

float Sphere::get_x() const
{
    return center.get_x();
}

float Sphere::get_y() const
{
    return center.get_y();
}

float Sphere::get_z() const
{
    return center.get_z();
}

float Sphere::get_r() const
{
    return r;
}

Color Sphere::get_color() const
{
    return color;
}

vector3 Sphere::get_center() const
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