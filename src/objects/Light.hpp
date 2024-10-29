#pragma once
#include "../raymath/Vector3.hpp"
#include "Color.hpp"

class Light {
private:
    Vector3 direction;
    Color color;
    float intensity;

public:
    Light(const Vector3& direction, const Color& color = Color(1,1,1), float intensity = 1.0f);
    Vector3 get_direction() const;
    Color get_color() const;
    float get_intensity() const;
};
