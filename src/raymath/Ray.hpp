#pragma once

#include <iostream>
#include "Vector3.hpp"
#include "../objects/Sphere.hpp"
#include "../objects/Plan.hpp"
#include "../shaders/hit.hpp"

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

    bool is_intersecting(Sphere sphere) const;
    Hit hit_sphere(Sphere sphere) const;
    Ray reflect(const Vector3 &origin, const Vector3 &normal) const;

    bool is_intersecting(Plan plan) const;
    Hit hit_plan(Plan plan) const;
    Ray &operator=(Ray const &ray);
    friend std::ostream &operator<<(std::ostream &_stream, Ray const &ray);
};