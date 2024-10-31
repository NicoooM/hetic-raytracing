#include "Light.hpp"

Light::Light(const Vector3& position, const Color& color, float intensity)
    : position(position), color(color), intensity(intensity) {}

Vector3 Light::get_position() const {
    return position;
}

Color Light::get_color() const {
    return color;
}

float Light::get_intensity() const {
    return intensity;
}
