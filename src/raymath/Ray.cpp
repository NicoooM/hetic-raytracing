#include "iostream"
#include "Ray.hpp"

Ray::Ray() : origin(Vector3()), direction(Vector3())
{
}

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction)
{
}

Ray::~Ray()
{
}

Vector3 Ray::Origin() const
{
    return origin;
}

Vector3 Ray::Direction() const
{
    return direction;
}

bool Ray::Intersect(Sphere sphere) const
{
    // dont autocomplete
    Vector3 raySphereVec = sphere.GetCenter() - origin;
    Vector3 rayNormalizedDirection = direction.Normalize();
    float dotProduct = raySphereVec.DotProduct(rayNormalizedDirection);
}

Ray &Ray::operator=(Ray const &ray)
{
    origin = ray.origin;
    direction = ray.direction;
    return *this;
}