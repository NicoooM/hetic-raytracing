#pragma once

#include "Color.hpp"
#include "../raymath/Vector3.hpp"

class Light {
private:
    Vector3 position;
    Color color;
    float intensity;

public:
    Light(const Vector3& position, const Color& color = Color(1,1,1), float intensity = 1.0f);
    Vector3 get_position() const;
    Color get_color() const;
    float get_intensity() const;
};
