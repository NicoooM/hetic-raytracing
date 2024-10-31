#pragma once

#include "Shape.hpp"
#include "Color.hpp"
#include "../raymath/Vector3.hpp"

class Ray;

class Cube : public Shape {
private:
    Vector3 center;
    float side_length;
    Color color;

public:
    Cube(Vector3 center, float side_length, Color color);
    ~Cube();

    Color get_color() const override;
    Hit intersect(const Ray& ray) const override;
}; 