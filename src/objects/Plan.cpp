#include "Plan.hpp"
#include "../raymath/Vector3.hpp"

Plan::Plan(const Vector3& point, const Vector3& normal)
    : point(point), normal(normal)
{
}

Plan::~Plan()
{
}

const Vector3& Plan::getPoint() const
{
    return point;
}

const Vector3& Plan::getNormal() const
{
    return normal;
}

void Plan::setPoint(const Vector3& point)
{
    this->point = point;
}

void Plan::setNormal(const Vector3& normal)
{
    this->normal = normal;
}
