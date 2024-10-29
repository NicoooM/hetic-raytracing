#pragma once
#include "../raymath/Vector3.hpp"
#include "../raymath/Ray.hpp"

class Camera {
private:
    Vector3 origin;
    float focal_length;
    float aspect_ratio;

public:
    Camera(const Vector3& origin = Vector3(0, 0, 0), float focal_length = 1.0f);
    Ray generate_ray(float x, float y, int width, int height) const;
    Vector3 get_origin() const;
};
