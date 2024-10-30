#include <iostream>
#include "Ray.hpp"
#include "Vector3.hpp"
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

bool Ray::is_intersecting(Sphere sphere) const
{
    Vector3 raySphereVec = sphere.get_center() - origin;

    Vector3 ray_normalized_direction = direction.normalize();
    float dot_product = raySphereVec.dot_product(ray_normalized_direction);

    Vector3 projection = ray_normalized_direction * dot_product;
    projection = origin + projection;
    Vector3 translation = projection - sphere.get_center();
    float distance = translation.pythagorean();

    if (distance > sphere.get_r())
    {
        return false;
    }

    return true;
}

Hit Ray::hit_sphere(Sphere sphere) const
{
    Vector3 origin_to_center_vec = origin - sphere.get_center();

    float quadratic_a = direction.dot_product(direction);
    float quadratic_b = 2.0f * origin_to_center_vec.dot_product(direction);
    float quadratic_c = origin_to_center_vec.dot_product(origin_to_center_vec) - sphere.get_r() * sphere.get_r();

    float intersection_discriminant = quadratic_b * quadratic_b - 4 * quadratic_a * quadratic_c;

    if (intersection_discriminant < 0)
        return Hit::no_hit();

    float nearest_intersection_dist = (-quadratic_b - sqrt(intersection_discriminant)) / (2.0f * quadratic_a);

    if (nearest_intersection_dist < 0)
    {
        nearest_intersection_dist = (-quadratic_b + sqrt(intersection_discriminant)) / (2.0f * quadratic_a);
        if (nearest_intersection_dist < 0)
            return Hit::no_hit();
    }

    Vector3 intersection_point = origin + direction * nearest_intersection_dist;

    Vector3 surface_normal = (intersection_point - sphere.get_center()).normalize();

    return Hit(nearest_intersection_dist, intersection_point, surface_normal);
}

Ray Ray::reflect(const Vector3 &hit_point, const Vector3 &normal) const
{
    float offset = 0.001f;
    Vector3 normalized_direction = direction.normalize();
    Vector3 reflected_direction = normalized_direction - 2 * normal.dot_product(normalized_direction) * normal;
    return Ray(hit_point + normal * offset, reflected_direction);
}

Hit Ray::hit_plan(Plan plan) const
{
    Vector3 normal = plan.get_normal();
    Vector3 point_on_plan = plan.get_point();

    float denom = normal.dot_product(direction);
    if (fabs(denom) < 1e-6)
    {
        return Hit::no_hit(); // Le rayon est parallèle au plan
    }

    float t = (point_on_plan - origin).dot_product(normal) / denom;
    if (t < 0)
    {
        return Hit::no_hit(); // Le plan est derrière le rayon
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

std::ostream &operator<<(std::ostream &_stream, Ray const &ray)
{
    _stream << "Ray(" << ray.origin << ", " << ray.direction << ")";
    return _stream;
}