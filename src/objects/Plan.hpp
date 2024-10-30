#pragma once


#include "../raymath/Vector3.hpp"

class Plan
{
private:
    Vector3 point;
    Vector3 normal;

public:
    Plan(const Vector3& point, const Vector3& normal);
    ~Plan();

    const Vector3& getPoint() const;
    const Vector3& getNormal() const;
    void setPoint(const Vector3& point);
    void setNormal(const Vector3& normal);
};
