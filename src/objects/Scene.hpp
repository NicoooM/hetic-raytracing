#pragma once

#include <vector>
#include "Sphere.hpp"
#include "Plan.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "../rayimage/Image.hpp"

class Scene
{
private:
    std::vector<Sphere> objects;
    std::vector<Plan> plans;
    std::vector<Light> lights;
    Camera camera;
    Color background_color;
    int width;
    int height;

    Color calculate_pixel_color(const Ray& ray, const Vector3& pixel_position) const;
    Color calculate_phong_lighting( const Vector3& hit_point, const Vector3& normal, 
                                    const Vector3& view_dir, const Color& base_color ) const;

public:
    Scene(int width, int height, const Camera& camera);

    void add_object(const Sphere& object);
    void add_light(const Light& light);
    Image render() const;
};