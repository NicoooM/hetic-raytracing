#include "Light.hpp"

Light::Light(const Vector3& direction, const Color& color, float intensity)
    : direction(direction.normalize()), color(color), intensity(intensity) {}

Vector3 Light::get_direction() const {
    return direction;
}

Color Light::get_color() const {
    return color;
}

float Light::get_intensity() const {
    return intensity;
}
