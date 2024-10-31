#pragma once

#include "Shape.hpp"
#include "Color.hpp"
#include "../raymath/Vector3.hpp"

class Ray;  

class Sphere : public Shape {
private:
    Vector3 center;
    Color color;
    float r = 0;

public:
    Sphere();
    Sphere(Vector3 center, float r, Color color);
    ~Sphere();

    float get_x() const;
    float get_y() const;
    float get_z() const;
    float get_r() const;
    Color get_color() const override;
    Vector3 get_center() const;

    Sphere &operator=(Sphere const &sphere);

    friend std::ostream &operator<<(std::ostream &_stream, Sphere const &sphere);

    Hit intersect(const Ray& ray) const override;
};