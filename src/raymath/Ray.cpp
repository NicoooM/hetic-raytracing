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
    Vector3 raySphereVec = sphere.GetCenter() - origin;
    Vector3 rayNormalizedDirection = direction.Normalize();
    float dotProduct = raySphereVec.DotProduct(rayNormalizedDirection);

    if (dotProduct < 0)
        return false;

    Vector3 projection = rayNormalizedDirection * dotProduct;
    projection = origin + projection;
    Vector3 translation = projection - sphere.GetCenter();
    float distance = translation.Pythagorean();

    return distance <= sphere.R();
}

Ray &Ray::operator=(Ray const &ray)
{
    origin = ray.origin;
    direction = ray.direction;
    return *this;
}