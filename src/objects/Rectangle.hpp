#pragma once

#include <iostream>
#include "Color.hpp"
#include "../raymath/Vector3.hpp"

class Rectangle
{
private:
    Vector3 center;
    Color color;

public:
    Rectangle();
    Rectangle(Vector3 center, Color color);
    ~Rectangle();

    float get_x() const;
    float get_y() const;
    float get_z() const;
    Color get_color() const;
    Vector3 get_center() const;

    Rectangle &operator=(Rectangle const &rectangle);
    friend std::ostream &operator<<(std::ostream &_stream, Rectangle const &rectangle);
};
