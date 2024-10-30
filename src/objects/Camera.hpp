#pragma once

#include "../raymath/Vector3.hpp"
#include "../raymath/Ray.hpp"

class Camera {
public:
    Camera(const Vector3& origin, float focal_length);
    Ray generate_ray(float u, float v, int width, int height) const;

private:
    Vector3 origin;
    float focal_length;
};
