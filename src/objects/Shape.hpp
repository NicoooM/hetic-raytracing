#pragma once

#include "../raymath/Vector3.hpp"
#include "Color.hpp"
#include "../shaders/hit.hpp"

class Ray;

class Shape {
public:
    virtual ~Shape() = default;
    virtual Hit intersect(const Ray& ray) const = 0;
    virtual Color get_color() const = 0;
}; 