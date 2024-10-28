#pragma once

#include "Vector3.hpp"
#include "../objects/Sphere.hpp"
#include <iostream>

class Ray
{
private:
    Vector3 origin;
    Vector3 direction;

public:
    Ray();
    Ray(Vector3 origin, Vector3 direction);
    ~Ray();

    Vector3 get_origin() const;
    Vector3 get_direction() const;
    Vector3 hit_sphere(Sphere sphere) const;
    bool is_intersecting(Sphere sphere) const;

    Ray &operator=(Ray const &ray);
    friend std::ostream &operator<<(std::ostream &_stream, Ray const &ray);
};