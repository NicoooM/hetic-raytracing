#include "Camera.hpp"

Camera::Camera(const Vector3& origin, float focal_length)
    : origin(origin), focal_length(focal_length) {}

Ray Camera::generate_ray(float x, float y, int width, int height) const {
    float aspect_ratio = float(width) / float(height);
    float scale = tan(focal_length * 0.5 *  (M_PI / 180));

    // Convert to NDC (Normalized Device Coordinates)
    auto pixel_normalized_device_coordinate_x = (x + 0.5f) / width;
    auto pixel_normalized_device_coordinate_y = (y + 0.5f) / height;
 
    // Convert to screen space (aspect ratio to aspect ratio) for X and (-1 to 1) for Y
    auto pixel_screen_x = (2 * pixel_normalized_device_coordinate_x - 1) * aspect_ratio;
    auto pixel_screen_y = 1 - 2 * pixel_normalized_device_coordinate_y;


    float final_pixel_x = pixel_screen_x * scale;
    float final_pixel_y = pixel_screen_y * scale;
    float final_pixel_z = 1;

    
    Vector3 pixel_position(
        final_pixel_x,
        final_pixel_y,
        final_pixel_z
    );
    
    return Ray(origin, (pixel_position - origin).normalize());
}

Vector3 Camera::get_origin() const {
    return origin;
}
