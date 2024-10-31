#include "Cube.hpp"
#include "../raymath/Ray.hpp"

Cube::Cube(Vector3 iCenter, float iSideLength, Color iColor)
    : center(iCenter), side_length(iSideLength), color(iColor) {}

Cube::~Cube() {}

Color Cube::get_color() const {
    return color;
}

Hit Cube::intersect(const Ray& ray) const {
    // Implémentation de l'intersection rayon-cube
    // Calculer les intersections avec les six faces du cube
    // Retourner le point d'intersection le plus proche
    // Pour simplifier, on peut utiliser l'algorithme de l'axe aligné (AABB)
    // à adapter selon votre structure de données et votre logique

    // Exemple simplifié d'intersection AABB
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

    if (tz_max < t_max)
        t_max = tz_max;

    if (t_min < 0)
        return Hit::no_hit();

    Vector3 hit_point = ray.get_origin() + ray.get_direction() * t_min;
    Vector3 normal; // Calculer la normale en fonction de la face touchée

    return Hit(t_min, hit_point, normal);
} 