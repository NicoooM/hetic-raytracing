#include <vector>

#include "../rayimage/Image.hpp"
#include "Sphere.hpp"
#include "Plan.hpp"
#include "Color.hpp"
#include "Camera.hpp"
#include "Light.hpp"

class Scene {
public:
    Scene(int width, int height, const Color& background_color, const Camera& camera);
    Image render() const;

private:
    std::vector<Sphere> objects;
    std::vector<Plan> plans;
    std::vector<Light> lights;
    Camera camera;
    int width;
    int height;
    Color background_color;

    Color calculate_pixel_color(const Ray& ray, const Vector3& pixel_position) const;
};