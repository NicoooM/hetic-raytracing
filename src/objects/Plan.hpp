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

    const Vector3& get_point() const;
    const Vector3& get_normal() const;
    void set_point(const Vector3& point);
    void set_normal(const Vector3& normal);
};
