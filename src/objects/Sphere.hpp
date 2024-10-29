#pragma once

#include <iostream>
#include "../raymath/Color.hpp"
#include "../raymath/Vector3.hpp"

class Sphere
{
private:
    Vector3 center;
    float r = 0;
    Color color;

public:
    Sphere();
    Sphere(Vector3 center, float r, Color color);
    ~Sphere();

    float get_x() const;
    float get_y() const;
    float get_z() const;
    float get_r() const;
    Color get_color() const;
    Vector3 get_center() const;

    Sphere &operator=(Sphere const &sphere);
    friend std::ostream &operator<<(std::ostream &_stream, Sphere const &sphere);
};