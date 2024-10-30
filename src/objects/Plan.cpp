#include "Plan.hpp"
#include "../raymath/Vector3.hpp"

Plan::Plan(const Vector3& point, const Vector3& normal)
    : point(point), normal(normal)
{
}

Plan::~Plan()
{
}

const Vector3& Plan::get_point() const
{
    return point;
}

const Vector3& Plan::get_normal() const
{
    return normal;
}

void Plan::set_point(const Vector3& point)
{
    this->point = point;
}

void Plan::set_normal(const Vector3& normal)
{
    this->normal = normal;
}
