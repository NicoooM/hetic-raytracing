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

    Vector3 projection = rayNormalizedDirection * dotProduct;
    projection = origin + projection;
    Vector3 translation = projection - sphere.get_center();
    float distance = translation.pythagorean();

    if (distance > sphere.get_r()) {
        return false;
    }

    return true;
}

Vector3 Ray::hit_sphere(Sphere sphere) const
{
    Vector3 distance_between_ray_origin_and_sphere_center = sphere.get_center() - origin;
    Vector3 ray_normalized_direction = direction.normalize();
    float dot_product = distance_between_ray_origin_and_sphere_center.dot_product(ray_normalized_direction);
    
    Vector3 projection = ray_normalized_direction * dot_product;
    projection = origin + projection;
    Vector3 center_to_projection = projection - sphere.get_center();
    float distance = center_to_projection.pythagorean();

    if (distance > sphere.get_r())
        return Vector3();
        

    float a = sqrt(sphere.get_r() * sphere.get_r() - distance * distance);

    Vector3 coordinate_of_intersection = projection + (a * (ray_normalized_direction * -1.0f));
 
    // if (origin.get_x() == 0 && origin.get_y() == 0 && origin.get_z() == 0) {
    //     std::cout << "coordinate_of_intersection: " << coordinate_of_intersection.get_x() << " " << coordinate_of_intersection.get_y() << " " << coordinate_of_intersection.get_z() << std::endl;
    //     std::cout << "Sphere: " << sphere.get_center().get_x() << " " << sphere.get_center().get_y() << " " << sphere.get_center().get_z() << std::endl;
    //     std::cout << "Sphere Rayon: " << sphere.get_r() << std::endl;
    //     std::cout << "Distance: " << distance << std::endl;
    // }
    
    return coordinate_of_intersection;
}


Ray &Ray::operator=(Ray const &ray)
{
    origin = ray.origin;
    direction = ray.direction;
    return *this;
}