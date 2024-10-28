#include <iostream>
#include "Ray.hpp"
#include "Vector3.hpp"

Ray::Ray() : origin(Vector3()), direction(Vector3())
{
}

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction)
{
}

Ray::~Ray()
{
}

Vector3 Ray::get_origin() const
{
    return origin;
}

Vector3 Ray::get_direction() const
{
    return direction;
}

bool Ray::is_intersecting(Sphere sphere) const
{
    Vector3 raySphereVec = sphere.get_center() - origin;
    Vector3 rayNormalizedDirection = direction.normalize();
    float dotProduct = raySphereVec.dot_product(rayNormalizedDirection);

    if (dotProduct < 0)
        return false;

    Vector3 projection = rayNormalizedDirection * dotProduct;
    projection = origin + projection;
    Vector3 translation = projection - sphere.get_center();
    float distance = translation.get_length();

    return distance <= sphere.get_r();
}


Vector3 Ray::hit_sphere(Sphere sphere) const
{
    Vector3 distance_between_ray_origin_and_sphere_center = sphere.get_center() - origin;
    Vector3 ray_normalized_direction = direction.normalize();
    float dot_product = distance_between_ray_origin_and_sphere_center.dot_product(ray_normalized_direction);
    
    Vector3 projection = ray_normalized_direction * dot_product;
    projection = origin + projection;
    Vector3 center_to_projection = projection - sphere.get_center();
    float distance = center_to_projection.get_length();

    if (distance > sphere.get_r())
        return Vector3();
        

    float a = sqrt(sphere.get_r() * sphere.get_r() - distance * distance);
    Vector3 coordinate_of_intersection =  projection + (ray_normalized_direction * a);
    return coordinate_of_intersection;
}

Ray &Ray::operator=(Ray const &ray)
{
    origin = ray.origin;
    direction = ray.direction;
    return *this;
}