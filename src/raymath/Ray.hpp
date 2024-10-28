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

    Vector3 Origin() const;
    Vector3 Direction() const;

    bool Intersect(Sphere sphere) const;

    Ray &operator=(Ray const &ray);
    friend std::ostream &operator<<(std::ostream &_stream, Ray const &ray);
};