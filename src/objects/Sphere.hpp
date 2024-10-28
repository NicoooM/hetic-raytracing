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

    float X() const;
    float Y() const;
    float Z() const;
    float R() const;
    Color GetColor() const;
    Vector3 GetCenter() const;

    Sphere &operator=(Sphere const &sphere);
    friend std::ostream &operator<<(std::ostream &_stream, Sphere const &sphere);
};