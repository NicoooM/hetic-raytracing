#include "Scene.hpp"
#include "../shaders/hit.hpp"

Scene::Scene(int width, int height, const Camera &camera)
    : width(width), height(height), camera(camera), background_color(0, 0, 0) {}

void Scene::add_object(const Sphere &object)
{
    objects.push_back(object);
}

void Scene::add_object(const Rectangle &object)
{
    rectangles.push_back(object);
}

void Scene::add_light(const Light &light)
{
    lights.push_back(light);
}

void Scene::set_background_color(const Color &color)
{
    background_color = color;
}

Image Scene::render(ShadingType shading_type) const
{
    Image image(width, height, background_color);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Ray ray = camera.generate_ray(x, y, width, height);
            Color pixel_color = calculate_pixel_color(ray, Vector3(x, y, 0), shading_type, 3);
            image.set_pixel(x, y, pixel_color);
        }
    }

    return image;
}

Color Scene::calculate_pixel_color(const Ray &ray, const Vector3 &pixel_position, ShadingType shading_type, int depth) const
{

    if (depth <= 0)
    {
        // Base case: background color or no further recursion allowed
        return Color(0, 0, 0); // black or background color
    }

    Color final_color(0, 0, 0); // initialize final color as black or background

    for (const auto &sphere : objects)
    {
        Hit hit = ray.hit_sphere(sphere);
        if (hit.HasCollision())
        {
            Vector3 hit_point = hit.Point();
            Vector3 normal = hit.Normal();
            Vector3 view_dir = (camera.get_origin() - hit_point).normalize();

            // Base color from lighting model (Phong or Cook-Torrance)
            Color base_color;
            if (shading_type == PHONG)
            {
                base_color = calculate_phong_lighting(hit_point, normal, view_dir, sphere.get_color());
            }
            else if (shading_type == COOK_TORRANCE)
            {
                // base_color = calculate_cook_torrance(hit_point, normal, view_dir, sphere.get_color());
            }

            float reflection_strength = 0.5; // Coefficient for reflective materials
            if (reflection_strength > 0)
            {
                Ray reflected_ray = ray.reflect(hit_point, normal);
                Color reflected_color = calculate_pixel_color(reflected_ray, hit_point, shading_type, depth - 1);
                base_color = base_color * (1.0f - reflection_strength) + reflected_color * reflection_strength;
            }

            final_color = base_color;
            break; // Assuming one hit per ray; if multiple, this may need adjustment
        }
    }

    for (const auto &rectangle : rectangles)
    {
        Hit hit = ray.hit_rectangle(rectangle);
        if (hit.HasCollision())
        {
            Vector3 hit_point = hit.Point();
            Vector3 normal = hit.Normal();
            Vector3 view_dir = (camera.get_origin() - hit_point).normalize();

            if (shading_type == PHONG)
            {
                return calculate_phong_lighting(hit_point, normal, view_dir, rectangle.get_color());
            }
            else if (shading_type == COOK_TORRANCE)
            {
                // return calculate_cook_torrance(hit_point, normal, view_dir, rectangle.get_color());
            }
        }
    }

    // float gradient = static_cast<float>(pixel_position.get_y()) / height;
    // return Color(0, 0, gradient);

    // If no objects are hit, return the background color (gradient)
    if (final_color == Color(0, 0, 0))
    {
        float gradient = static_cast<float>(pixel_position.get_y()) / height;
        return Color(0, 0, gradient); // background gradient
    }

    return final_color;
}

Color Scene::calculate_phong_lighting(const Vector3 &hit_point, const Vector3 &normal,
                                      const Vector3 &view_dir, const Color &base_color) const
{
    float ambient_coefficient = 0.2f;
    float diffuse_coefficient = 0.6f;
    float specular_coefficient = 0.4f;
    float ambient = 0.2f;
    float total_diffuse = 0.0f;
    float total_specular = 0.0f;

    for (const auto &light : lights)
    {
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
        std::min(1.0f, base_color.B() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)));
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
