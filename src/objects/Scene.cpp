#include "Scene.hpp"
#include "../shaders/hit.hpp"

Scene::Scene(int width, int height, const Camera &camera)
    : width(width), height(height), camera(camera), background_color(0, 0, 0)
{
    // Modifions la position du plan pour qu'il soit plus visible
    Plan default_plan(Vector3(0, -10, 0), Vector3(0, 1, 0)); // Position plus basse et normale vers le haut
    plans.push_back(default_plan);
}

void Scene::add_object(const Sphere &object)
{
    objects.push_back(object);
}

void Scene::add_light(const Light &light)
{
    lights.push_back(light);
}

Image Scene::render() const
{
    Image image(width, height, background_color);

    // Ray ray = camera.generate_ray(960, 540, width, height);
    // Vector3 origin = ray.get_origin();
    // std::cout << "origin: " << origin.get_x() << " " << origin.get_y() << " " << origin.get_z() << std::endl;
    // ray.hit_sphere(objects[0]);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Ray ray = camera.generate_ray(x, y, width, height);
            Color pixel_color = calculate_pixel_color(ray, Vector3(x, y, 0), 3);
            image.set_pixel(x, y, pixel_color);
        }
    }

    return image;
}

Color Scene::calculate_pixel_color(const Ray &ray, const Vector3 &pixel_pos, int depth) const
{
    if (depth == 0)
        return background_color;

    Color final_color(0, 0, 0);

    float closest_distance = std::numeric_limits<float>::infinity();
    Hit closest_hit;
    bool is_plan = false;
    bool is_sphere = false;
    Color color;

    // Check intersections with planes
    for (const Plan &plan : plans)
    {
        Hit hit = ray.hit_plan(plan);
        if (hit.HasCollision() && hit.Distance() < closest_distance)
        {
            closest_distance = hit.Distance();
            closest_hit = hit;
            is_plan = true;
            is_sphere = false;
        }
    }

    // Check intersections with spheres
    for (const Sphere &sphere : objects)
    {
        Hit hit = ray.hit_sphere(sphere);
        if (hit.HasCollision() && hit.Distance() < closest_distance)
        {
            closest_distance = hit.Distance();
            closest_hit = hit;
            is_sphere = true;
            is_plan = false;
            color = sphere.get_color();
        }
    }

    // Handle sphere intersection with reflection
    if (is_sphere)
    {
        Vector3 hit_point = closest_hit.Point();
        Vector3 normal = closest_hit.Normal();
        Vector3 view_dir = (camera.get_origin() - hit_point).normalize();

        Color base_color = calculate_phong_lighting(hit_point, normal, view_dir, color);

        // Reflection calculation
        float reflection_strength = 0.5f;
        if (reflection_strength > 0)
        {
            Ray reflected_ray = ray.reflect(hit_point, normal);
            Color reflected_color = calculate_pixel_color(reflected_ray, hit_point, depth - 1);
            base_color = base_color * (1.0f - reflection_strength) + reflected_color * reflection_strength;
        }

        final_color = base_color; // Store the combined color with reflection
    }
    // Handle plane intersection with checkerboard pattern
    else if (is_plan)
    {
        Vector3 hit_point = closest_hit.Point();

        // Checkerboard pattern
        float grid_size = 5.0f;
        float x = hit_point.get_x();
        float z = hit_point.get_z();
        int x_case = static_cast<int>(floor(x / grid_size));
        int z_case = static_cast<int>(floor(z / grid_size));

        bool is_white = (x_case + z_case) % 2 == 0;
        final_color = is_white ? Color(0.8f, 0.8f, 0.8f) : Color(0.2f, 0.2f, 0.2f);
    }
    else
    {
        // Background gradient if no objects hit
        float gradient = static_cast<float>(pixel_pos.get_y()) / height;
        return Color(0, 0, gradient);
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

    return Color(
        std::min(1.0f, base_color.R() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.G() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.B() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse + specular_coefficient * total_specular)));
}
