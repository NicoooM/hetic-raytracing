#include "Scene.hpp"
#include "../shaders/hit.hpp"

Scene::Scene(int width, int height, const Camera& camera)
    : width(width), height(height), camera(camera), background_color(0,0,0) {
    // Modifions la position du plan pour qu'il soit plus visible
    Plan default_plan(Vector3(0, 2, 0), Vector3(0, 1, 0)); // Position plus basse et normale vers le haut
    plans.push_back(default_plan);
}

void Scene::add_object(const Sphere& object) {
    objects.push_back(object);
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

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Ray ray = camera.generate_ray(x, y, width, height);
            Color pixel_color = calculate_pixel_color(ray, Vector3(x, y, 0), shading_type);
            image.set_pixel(x, y, pixel_color);
        }
    }

    return image;
}

Color Scene::calculate_pixel_color(const Ray& ray, const Vector3& pixel_pos, ShadingType shading_type) const {
    float closest_distance = std::numeric_limits<float>::infinity();
    Hit closest_hit;
    bool is_plan = false;
    bool is_sphere = false;

    // Vérifier les intersections avec les plans
    for (const Plan& plan : plans) {
        Hit hit = ray.hit_plan(plan);
        if (hit.HasCollision() && hit.Distance() < closest_distance) {
            closest_distance = hit.Distance();
            closest_hit = hit;
            is_plan = true;
            is_sphere = false;
        }
    }

    // Vérifier les intersections avec les sphères
    for (const Sphere& sphere : objects) {
        Hit hit = ray.hit_sphere(sphere);
        if (hit.HasCollision() && hit.Distance() < closest_distance) {
            closest_distance = hit.Distance();
            closest_hit = hit;
            is_sphere = true;
            is_plan = false;
        }
    }

    // Si nous avons touché quelque chose
    if (is_sphere) {
        // Retourner la couleur de la sphère
        Vector3 hit_point = closest_hit.Point();
        Vector3 normal = closest_hit.Normal();
        Vector3 view_dir = (camera.get_origin() - hit_point).normalize();
        
        // Trouver la sphère touchée
        for (const Sphere& sphere : objects) {
            if (ray.hit_sphere(sphere).HasCollision()) {
                return calculate_phong_lighting(hit_point, normal, view_dir, sphere.get_color());
            }
        }
    } else if (is_plan) {
        Vector3 hit_point = closest_hit.Point();
        
        // Créer un motif de grille
        float grid_size = 1.0f;
        float x = hit_point.get_x();
        float z = hit_point.get_z();
        
        // Normaliser les coordonnées pour la grille
        float x_grid = fmod(abs(x), grid_size);
        float z_grid = fmod(abs(z), grid_size);
        
        // Créer l'effet de grille
        bool is_line = x_grid < 0.1f || z_grid < 0.1f;
        
        if (is_line) {
            return Color(0.2f, 0.2f, 0.2f); // Lignes noires
        } else {
            return Color(0.8f, 0.8f, 0.8f); // Cases blanches
        }
    }

    return background_color;
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

        std::cout << "Ambient: " << ambient_coefficient * ambient << std::endl;
        std::cout << "Diffuse: " << diffuse_coefficient * total_diffuse << std::endl;
        std::cout << "Specular: " << specular_coefficient * total_specular << std::endl;
        std::cout << "Base color: R=" << base_color.R() << " G=" << base_color.G() << " B=" << base_color.B() << std::endl;
        std::cout << "Total: " << ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular << std::endl;

    return Color(
        std::min(1.0f, base_color.R() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.G() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.B() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular))
    );
}

// Color Scene::calculate_cook_torrance(const Vector3& hit_point, const Vector3& normal,
//                                    const Vector3& view_dir, const Color& base_color) const {
//     // Material parameters
//     float roughness = 0.3f; // Surface roughness
//     float metallic = 0.0f;  // Metallic factor
//     float f0 = 0.04f;       // Base reflectivity for non-metals

//     Color total_radiance(0, 0, 0);
    
//     for (const auto& light : lights) {
//         Vector3 light_dir = light.get_direction();
//         Vector3 half_vec = (view_dir + light_dir).normalize();
        
//         float NdotV = std::max(normal.dot_product(view_dir), 0.0f);
//         float NdotL = std::max(normal.dot_product(light_dir), 0.0f);
        
//         if (NdotL > 0) {
//             // Cook-Torrance BRDF components
//             float D = distribution(normal, half_vec, roughness);
//             float G = geometric_shadowing(normal, view_dir, light_dir, half_vec);
//             float F = fresnel(view_dir, half_vec, f0);
            
//             float numerator = D * G * F;
//             float denominator = 4.0f * NdotV * NdotL + 0.001f; // Prevent division by zero
//             float specular = numerator / denominator;
            
//             // Combine diffuse and specular components
//             float kD = (1.0f - F) * (1.0f - metallic);
            
//             Color radiance = base_color * (kD / M_PI + specular) * NdotL * light.get_intensity() * light.get_color();
//             total_radiance = total_radiance + radiance;
//         }
//     }
    
//     // Add ambient lighting
//     float ambient = 0.03f;
//     total_radiance = total_radiance + (base_color * ambient);
    
//     // Tone mapping and gamma correction could be added here
//     return Color(
//         std::min(1.0f, total_radiance.R()),
//         std::min(1.0f, total_radiance.G()),
//         std::min(1.0f, total_radiance.B())
//     );
// }

// float Scene::geometric_shadowing(const Vector3& normal, const Vector3& view_dir,
//                                const Vector3& light_dir, const Vector3& half_vec) const {
//     float NdotV = std::max(normal.dot_product(view_dir), 0.0f);
//     float NdotL = std::max(normal.dot_product(light_dir), 0.0f);
//     float NdotH = std::max(normal.dot_product(half_vec), 0.0f);
//     float VdotH = std::max(view_dir.dot_product(half_vec), 0.0f);
    
//     float r = 0.5f; // Roughness parameter
//     float k = ((r + 1) * (r + 1)) / 8.0f;
    
//     float geo1 = NdotV / (NdotV * (1 - k) + k);
//     float geo2 = NdotL / (NdotL * (1 - k) + k);
    
//     return geo1 * geo2;
// }

// float Scene::fresnel(const Vector3& view_dir, const Vector3& half_vec, float f0) const {
//     float VdotH = std::max(view_dir.dot_product(half_vec), 0.0f);
//     return f0 + (1.0f - f0) * std::pow(1.0f - VdotH, 5.0f);
// }

// float Scene::distribution(const Vector3& normal, const Vector3& half_vec, float roughness) const {
//     float NdotH = std::max(normal.dot_product(half_vec), 0.0f);
//     float alpha2 = roughness * roughness;
    
//     float NdotH2 = NdotH * NdotH;
//     float denom = NdotH2 * (alpha2 - 1.0f) + 1.0f;
    
//     return alpha2 / (M_PI * denom * denom);
// }





