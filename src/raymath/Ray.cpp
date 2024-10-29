#include <iostream>
#include "Ray.hpp"
#include "Vector3.hpp"
#include "../objects/Rectangle.hpp"
#include "../shaders/hit.hpp"

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

// TODO: Maybe remove this function because we do the same thing in hit_sphere
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
    float distance = translation.pythagorean();

    return distance <= sphere.get_r();
}

bool Ray::is_intersecting(Rectangle rectangle) const {
    // Supposons que le rectangle soit aligné avec les axes pour simplifier
    Vector3 normal = Vector3(0, 0, 1); // Normal du plan du rectangle
    Vector3 center = rectangle.get_center();

    // Calculer t pour l'intersection du rayon avec le plan
    float denom = normal.dot_product(direction);
    if (fabs(denom) < 1e-6) {
        return false; // Le rayon est parallèle au plan
    }

    float t = (center - origin).dot_product(normal) / denom;
    if (t < 0) {
        return false; // Le plan est derrière le rayon
    }

    // Calculer le point d'intersection
    Vector3 hit_point = origin + direction * t;

    // Vérifier si le point est à l'intérieur des limites du rectangle
    // Supposons que le rectangle soit centré sur 'center' avec une largeur et une hauteur données
    float half_width = rectangle.width / 2.0;
    float half_height = rectangle.height / 2.0;

    if (fabs(hit_point.get_x() - center.get_x()) <= half_width &&
        fabs(hit_point.get_y() - center.get_y()) <= half_height) {
        return true;
    }

    return false; // Pas d'intersection
}

Hit Ray::hit_sphere(Sphere sphere) const {
    Vector3 distance_between_ray_origin_and_sphere_center = sphere.get_center() - origin;
    Vector3 ray_normalized_direction = direction.normalize();
    float dot_product = distance_between_ray_origin_and_sphere_center.dot_product(ray_normalized_direction);
    
    Vector3 projection = ray_normalized_direction * dot_product;
    projection = origin + projection;
    Vector3 center_to_projection = projection - sphere.get_center();
    float distance = center_to_projection.pythagorean();

    if (distance > sphere.get_r())
        return Hit::NoHit();
        
    float a = sqrt(sphere.get_r() * sphere.get_r() - distance * distance);
    Vector3 coordinate_of_intersection =  projection + (ray_normalized_direction * a);
    Vector3 normal = (coordinate_of_intersection - sphere.get_center()).normalize();
    return Hit(distance, coordinate_of_intersection, normal);
}

Hit Ray::hit_rectangle(Rectangle rectangle) const 
{
    // Supposons que le rectangle soit aligné avec les axes pour simplifier
    Vector3 normal = Vector3(0, 0, 1); // Normal du plan du rectangle
    Vector3 center = rectangle.get_center();

    // Calculer t pour l'intersection du rayon avec le plan
    float denom = normal.dot_product(direction);
    if (fabs(denom) < 1e-6) {
        return Hit::NoHit(); // Le rayon est parallèle au plan
    }

    float t = (center - origin).dot_product(normal) / denom;
    if (t < 0) {
        return Hit::NoHit(); // Le plan est derrière le rayon
    }

    // Calculer le point d'intersection
    Vector3 hit_point = origin + direction * t;

    // Vérifier si le point est à l'intérieur des limites du rectangle
    // Supposons que le rectangle soit centré sur 'center' avec une largeur et une hauteur données
    float half_width = rectangle.width / 2.0;
    float half_height = rectangle.height / 2.0;

    if (fabs(hit_point.get_x() - center.get_x()) <= half_width &&
        fabs(hit_point.get_y() - center.get_y()) <= half_height) {
        return Hit(t, hit_point, normal);
    }

    return Hit::NoHit(); // Pas d'intersection
}

Hit Ray::hit_plan(Plan plan) const {
    Vector3 normal = plan.getNormal();
    Vector3 point_on_plan = plan.getPoint();

    float denom = normal.dot_product(direction);
    if (fabs(denom) < 1e-6) {
        return Hit::NoHit(); // Le rayon est parallèle au plan
    }

    float t = (point_on_plan - origin).dot_product(normal) / denom;
    if (t < 0) {
        return Hit::NoHit(); // Le plan est derrière le rayon
    }

    Vector3 hit_point = origin + direction * t;
    return Hit(t, hit_point, normal);
}

Ray &Ray::operator=(Ray const &ray)
{
    origin = ray.origin;
    direction = ray.direction;
    return *this;
}