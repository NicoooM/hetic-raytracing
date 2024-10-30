#include "Scene.hpp"
#include "../shaders/hit.hpp"

Scene::Scene(int width, int height, const Camera& camera)
    : width(width), height(height), camera(camera), background_color(0,0,0) {
    // Ajout d'un plan par défaut
    Plan default_plan(Vector3(0, 1, 0), Vector3(0, 1, 0)); // Position et normale du plan
    plans.push_back(default_plan);
}

void Scene::add_object(const Sphere& object) {
    objects.push_back(object);
}

void Scene::add_object(const Rectangle& object) {
    rectangles.push_back(object);
}

void Scene::add_object(const Plan& object) {
    plans.push_back(object);
}

void Scene::add_light(const Light& light) {
    lights.push_back(light);
}

void Scene::set_background_color(const Color& color) {
    background_color = color;
}

Image Scene::render(ShadingType shading_type) const {
    Image image(width, height, background_color);

    // Ray ray = camera.generate_ray(960, 540, width, height);
    // Vector3 origin = ray.get_origin();
    // std::cout << "origin: " << origin.get_x() << " " << origin.get_y() << " " << origin.get_z() << std::endl;
    // ray.hit_sphere(objects[0]);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Ray ray = camera.generate_ray(x, y, width, height);
            Color pixel_color = calculate_pixel_color(ray, Vector3(x, y, 0), shading_type);
            image.set_pixel(x, y, pixel_color);
        }
    }

    return image;
}

Color Scene::calculate_pixel_color(const Ray& ray, const Vector3& pixel_position, ShadingType shading_type) const {
    for (const auto& sphere : objects) {
        Hit hit = ray.hit_sphere(sphere);
        if (hit.HasCollision()) {
            Vector3 hit_point = hit.Point();
            Vector3 normal = hit.Normal();
            Vector3 view_dir = (camera.get_origin() - hit_point).normalize();
            
            // Create color based on normal vector components
            // Map normal components from [-1,1] to [0,1] range
            // float r = (normal.get_x() + 1.0f) * 0.5f;
            // float g = (normal.get_y() + 1.0f) * 0.5f; 
            // float b = (normal.get_z() + 1.0f) * 0.5f;
            // return Color(r, g, b);
            
            if (shading_type == PHONG) {
                return calculate_phong_lighting(hit_point, normal, view_dir, sphere.get_color());
            } else if (shading_type == COOK_TORRANCE) {
                // return calculate_cook_torrance(hit_point, normal, view_dir, sphere.get_color());
            }
        }
    }

    for (const auto& rectangle : rectangles) {
        Hit hit = ray.hit_rectangle(rectangle);
        if (hit.HasCollision()) {
            Vector3 hit_point = hit.Point();
            Vector3 normal = hit.Normal();
            Vector3 view_dir = (camera.get_origin() - hit_point).normalize();
            
            if (shading_type == PHONG) {
                return calculate_phong_lighting(hit_point, normal, view_dir, rectangle.get_color());
            } else if (shading_type == COOK_TORRANCE) {
                // return calculate_cook_torrance(hit_point, normal, view_dir, rectangle.get_color());
            }
        }
    }
    
    for (const auto& plan : plans) {
        Hit hit = ray.hit_plan(plan);
        if (hit.HasCollision()) {
            Vector3 hit_point = hit.Point();
            Vector3 normal = hit.Normal();
            Vector3 view_dir = (camera.get_origin() - hit_point).normalize();
            
            if (shading_type == PHONG) {
            return calculate_phong_lighting(hit_point, normal, view_dir, Color(1.0, 1.0, 0.0)); // Couleur jaune
        } else if (shading_type == COOK_TORRANCE) {
                // return calculate_cook_torrance(hit_point, normal, view_dir, Color(0.0, 1.0, 0.0));
            }
        }
    }
    
    float gradient = static_cast<float>(pixel_position.get_y()) / height;
    return Color(0, 0, gradient);
}

Color Scene::calculate_phong_lighting(const Vector3& hit_point, const Vector3& normal, 
                                  const Vector3& view_dir, const Color& base_color) const {
    float ambient_coefficient = 0.2f;
    float diffuse_coefficient = 0.6f;
    float specular_coefficient = 0.4f;
    float ambient = 0.2f;
    float total_diffuse = 0.0f;
    float total_specular = 0.0f;

    for (const auto& light : lights) {
        Vector3 light_dir = light.get_direction();
        Vector3 reflect_dir = (light_dir * -1 + normal * (2 * light_dir.dot_product(normal))).normalize();
        
        float diffuse = std::max(0.0f, normal.dot_product(light_dir));
        float specular = std::pow(std::max(0.0f, view_dir.dot_product(reflect_dir)), 16.0f);
        
        total_diffuse += diffuse * light.get_intensity();
        total_specular += specular * light.get_intensity();
    }

    total_diffuse /= lights.size();
    total_specular /= lights.size();

        // std::cout << "Ambient: " << ambient_coefficient * ambient << std::endl;
        // std::cout << "Diffuse: " << diffuse_coefficient * total_diffuse << std::endl;
        // std::cout << "Specular: " << specular_coefficient * total_specular << std::endl;
        // std::cout << "Base color: R=" << base_color.R() << " G=" << base_color.G() << " B=" << base_color.B() << std::endl;
        // std::cout << "Total: " << ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular << std::endl;

    return Color(
        std::min(1.0f, base_color.R() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.G() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.B() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular))
    );
}

