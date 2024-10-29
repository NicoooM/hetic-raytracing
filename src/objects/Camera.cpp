#include "Camera.hpp"

Camera::Camera(const Vector3& origin, float focal_length)
    : origin(origin), focal_length(focal_length) {}

Ray Camera::generate_ray(float x, float y, int width, int height) const {
    Vector3 pixel_position(
        (x - width/2) / 100.0,
        (y - height/2) / 100.0, 
        focal_length
    );
    return Ray(origin, (pixel_position - origin).normalize());
}

Vector3 Camera::get_origin() const {
    return origin;
}
