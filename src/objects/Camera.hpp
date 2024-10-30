#pragma once

#include "../raymath/Vector3.hpp"
#include "../raymath/Ray.hpp"

class Camera
{

private:
    Vector3 origin;
    float focal_length;
    
public:
    Camera(const Vector3& origin, float focal_length);

    Ray generate_ray(float u, float v, int width, int height) const;
    Vector3 get_origin() const;

};
