#include "Cube.hpp"
#include "../raymath/Ray.hpp"

Cube::Cube(Vector3 iCenter, float iSideLength, Color iColor)
    : center(iCenter), side_length(iSideLength), color(iColor) {}

Cube::~Cube() {}

Color Cube::get_color() const {
    return color;
}

Hit Cube::intersect(const Ray& ray) const {
    Vector3 min = center - Vector3(side_length / 2, side_length / 2, side_length / 2);
    Vector3 max = center + Vector3(side_length / 2, side_length / 2, side_length / 2);

    float t_min = (min.get_x() - ray.get_origin().get_x()) / ray.get_direction().get_x();
    float t_max = (max.get_x() - ray.get_origin().get_x()) / ray.get_direction().get_x();

    if (t_min > t_max) std::swap(t_min, t_max);

    float ty_min = (min.get_y() - ray.get_origin().get_y()) / ray.get_direction().get_y();
    float ty_max = (max.get_y() - ray.get_origin().get_y()) / ray.get_direction().get_y();

    if (ty_min > ty_max) std::swap(ty_min, ty_max);

    if ((t_min > ty_max) || (ty_min > t_max))
        return Hit::no_hit();

    if (ty_min > t_min)
        t_min = ty_min;

    if (ty_max < t_max)
        t_max = ty_max;

    float tz_min = (min.get_z() - ray.get_origin().get_z()) / ray.get_direction().get_z();
    float tz_max = (max.get_z() - ray.get_origin().get_z()) / ray.get_direction().get_z();

    if (tz_min > tz_max) std::swap(tz_min, tz_max);

    if ((t_min > tz_max) || (tz_min > t_max))
        return Hit::no_hit();

    if (tz_min > t_min)
        t_min = tz_min;

    if (t_min < 0)
        return Hit::no_hit();

    Vector3 hit_point = ray.get_origin() + ray.get_direction() * t_min;
    
    // Calcul de la normale en fonction de la face touchée
    Vector3 normal;
    float epsilon = 0.0001f;
    
    if (std::abs(hit_point.get_x() - min.get_x()) < epsilon)
        normal = Vector3(-1, 0, 0);
    else if (std::abs(hit_point.get_x() - max.get_x()) < epsilon)
        normal = Vector3(1, 0, 0);
    else if (std::abs(hit_point.get_y() - min.get_y()) < epsilon)
        normal = Vector3(0, -1, 0);
    else if (std::abs(hit_point.get_y() - max.get_y()) < epsilon)
        normal = Vector3(0, 1, 0);
    else if (std::abs(hit_point.get_z() - min.get_z()) < epsilon)
        normal = Vector3(0, 0, -1);
    else
        normal = Vector3(0, 0, 1);

    return Hit(t_min, hit_point, normal);
} 