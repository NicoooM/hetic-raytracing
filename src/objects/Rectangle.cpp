#include <iostream>
#include "Rectangle.hpp"
#include "../raymath/Vector3.hpp"

Rectangle::Rectangle() : center(Vector3()), color(Color())
{
}

Rectangle::Rectangle(Vector3 iCenter, Color iColor) : center(iCenter), color(iColor)
{
    // Initialisation ou logique supplémentaire si nécessaire
}

Rectangle::~Rectangle()
{
    // Nettoyage si nécessaire
}

float Rectangle::get_x() const
{
    return center.get_x();
}

float Rectangle::get_y() const
{
    return center.get_y();
}

float Rectangle::get_z() const
{
    return center.get_z();
}

Color Rectangle::get_color() const // Renamed method
{
    return color;
}

Vector3 Rectangle::get_center() const
{
    return center;
}

Rectangle &Rectangle::operator=(Rectangle const &rectangle)
{
    center = rectangle.center;
    color = rectangle.color;
    return *this;
}

std::ostream &operator<<(std::ostream &_stream, Rectangle const &rectangle)
{
    return _stream << "Rectangle(" << rectangle.center << "," << rectangle.color << ")";
}
