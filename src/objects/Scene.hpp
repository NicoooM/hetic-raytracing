#pragma once

#include <vector>
#include "Sphere.hpp"
#include "Shape.hpp"
#include "Plan.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "../rayimage/Image.hpp"

class Scene
{
private:
    std::vector<Shape *> objects;
    std::vector<Plan> plans;
    std::vector<Light> lights;
    Camera camera;
    Color background_color;
    int width;
    int height;

public:
    Scene(int width, int height, const Camera &camera);
    void add_object(Shape *object);
    void add_light(const Light &light);
    void render_chunk(Image &image, int start_y, int end_y) const;
    void add_plan(const Plan &plan);
    Image render() const;

private:
    Color calculate_pixel_color(const Ray &ray, const Vector3 &pixel_position, int depth) const;
    Color calculate_phong_lighting(const Vector3 hit_point, const Vector3 &normal,
                                   const Vector3 &view_dir, const Color &base_color) const;
};