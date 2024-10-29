#pragma once
#include <vector>
#include "Sphere.hpp"
#include "Rectangle.hpp"
#include "../rayimage/Image.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Scene {
private:
    std::vector<Sphere> objects;
    std::vector<Rectangle> rectangles;
    std::vector<Light> lights;
    Camera camera;
    int width;
    int height;
    Color background_color;

public:
    Scene(int width, int height, const Camera& camera);
    void add_object(const Sphere& object);
    void add_object(const Rectangle& object);
    void add_light(const Light& light);
    void set_background_color(const Color& color);
    enum ShadingType {
        PHONG = 0,
        COOK_TORRANCE = 1
    };
    Image render(ShadingType shading_type = PHONG) const;

private:
    Color calculate_pixel_color(const Ray& ray, const Vector3& pixel_position, ShadingType shading_type) const;
    Color calculate_phong_lighting(const Vector3& hit_point, const Vector3& normal, 
                               const Vector3& view_dir, const Color& base_color) const;
    // Color calculate_cook_torrance(const Vector3& hit_point, const Vector3& normal,
    //                             const Vector3& view_dir, const Color& base_color) const;
                                
    // float geometric_shadowing(const Vector3& normal, const Vector3& view_dir, 
    //                         const Vector3& light_dir, const Vector3& half_vec) const;
    // float fresnel(const Vector3& view_dir, const Vector3& half_vec, float f0 = 0.04f) const;
    // float distribution(const Vector3& normal, const Vector3& half_vec, float roughness) const;
};