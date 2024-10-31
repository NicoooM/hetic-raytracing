#include "Scene.hpp"
#include "../shaders/hit.hpp"
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>

Scene::Scene(int width, int height, const Camera &camera)
    : width(width), height(height), camera(camera), background_color(0, 0, 0)
{
}

void Scene::add_plan(const Plan &plan)
{
    plans.push_back(plan);
}

void Scene::add_object(Shape *object)
{
    objects.push_back(object);
}

void Scene::add_light(const Light &light)
{
    lights.push_back(light);
}

Image Scene::render() const
{
    auto start_time = std::chrono::high_resolution_clock::now();

    Image image(width, height, background_color);
    int antialiasing_samples_per_pixel = 10;

    const unsigned int thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    const int chunk_size = height / thread_count;

    for (unsigned int i = 0; i < thread_count; i++)
    {
        int start_y = i * chunk_size;
        int end_y = (i == thread_count - 1) ? height : (i + 1) * chunk_size;

        threads.emplace_back([this, &image, start_y, end_y]()
                             { render_chunk(image, start_y, end_y); });
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Multithreaded render completed in: "
              << duration.count() << "ms" << std::endl;

    return image;
}

Color Scene::calculate_pixel_color(const Ray &ray, const Vector3 &pixel_pos, int depth) const
{

    Color final_color(0, 0, 0);
    float closest_distance = std::numeric_limits<float>::infinity();
    Hit closest_hit;
    bool is_plan = false;
    bool is_sphere = false;
    Color color;

    // Check if the ray intersects with the plans
    for (const Plan &plan : plans)
    {
        Hit hit = ray.hit_plan(plan);
        if (hit.has_collision() && hit.get_distance() < closest_distance)
        {
            closest_distance = hit.get_distance();
            closest_hit = hit;
            is_plan = true;
            is_sphere = false;
        }
    }

    // Check if the ray intersects with the shapes
    for (const Shape *shape : objects)
    {
        Hit hit = shape->intersect(ray);
        if (hit.has_collision() && hit.get_distance() < closest_distance)
        {
            closest_distance = hit.get_distance();
            closest_hit = hit;
            is_sphere = true;
            is_plan = false;
            color = shape->get_color();
        }
    }

    if (!is_sphere && !is_plan)
    {
        float gradient = static_cast<float>(pixel_pos.get_y()) / height;
        return Color(0, 0, gradient);
    }

    // Calculate the base color of the hit point
    if (is_sphere)
    {
        Vector3 hit_point = closest_hit.get_point();
        Vector3 normal = closest_hit.get_normal();
        Vector3 view_dir = (camera.get_origin() - hit_point).normalize();

        final_color = calculate_phong_lighting(hit_point, normal, view_dir, color);
    }
    else if (is_plan)
    {
        Vector3 hit_point = closest_hit.get_point();
        Vector3 normal = closest_hit.get_normal();
        Vector3 view_dir = (camera.get_origin() - hit_point).normalize();

        float grid_size = 5.0f;
        float x = hit_point.get_x();
        float z = hit_point.get_z();
        int x_case = static_cast<int>(floor(x / grid_size));
        int z_case = static_cast<int>(floor(z / grid_size));

        bool is_white = (x_case + z_case) % 2 == 0;
        Color white(1.0f, 1.0f, 1.0f);
        Color black(0.0f, 0.0f, 0.0f);
        final_color = is_white ? calculate_phong_lighting(hit_point, normal, view_dir, white) : calculate_phong_lighting(hit_point, normal, view_dir, black);
    }

    if (depth <= 0)
    {
        return final_color;
    }

    if ((is_sphere || is_plan) && depth > 0)
    {
        float reflMulti = is_sphere ? 0.5f : 0.1f;
        Vector3 hit_point = closest_hit.get_point();
        Vector3 normal = closest_hit.get_normal();

        // Calculate reflected ray
        Ray reflected_ray = ray.reflect(hit_point, normal);
        reflected_ray.get_origin() = hit_point + normal * 0.001f;

        Color reflected_color = calculate_pixel_color(reflected_ray, hit_point, depth - 1);

        final_color = final_color * (1.0f - reflMulti) + reflected_color * reflMulti;
    }

    return final_color;
}

Color Scene::calculate_phong_lighting(const Vector3 hit_point, const Vector3 &normal,
                                      const Vector3 &view_dir, const Color &base_color) const
{
    float ambient_coefficient = 0.2f;
    float diffuse_coefficient = 0.6f;
    float specular_coefficient = 0.4f;
    float ambient = 0.2f;
    float total_specular = 0.0f;
    float total_diffuse_r = 0.0f;
    float total_diffuse_g = 0.0f;
    float total_diffuse_b = 0.0f;

    for (const auto &light : lights)
    {
        Vector3 light_dir = (light.get_position() - hit_point).normalize();
        Vector3 reflect_dir = (light_dir * -1 + normal * (2 * light_dir.dot_product(normal))).normalize();

        float diffuse = std::max(0.0f, normal.dot_product(light_dir));
        float specular = std::pow(std::max(0.0f, view_dir.dot_product(reflect_dir)), 16.0f);

        total_diffuse_r += diffuse * light.get_intensity() * light.get_color().R();
        total_diffuse_g += diffuse * light.get_intensity() * light.get_color().G();
        total_diffuse_b += diffuse * light.get_intensity() * light.get_color().B();
        total_specular += specular * light.get_intensity();
    }

    total_diffuse_r /= lights.size();
    total_diffuse_g /= lights.size();
    total_diffuse_b /= lights.size();
    total_specular /= lights.size();

    return Color(
        std::min(1.0f, base_color.R() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse_r + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.G() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse_g + specular_coefficient * total_specular)),
        std::min(1.0f, base_color.B() * (ambient_coefficient * ambient + diffuse_coefficient * total_diffuse_b + specular_coefficient * total_specular)));
}

void Scene::render_chunk(Image &image, int start_y, int end_y) const
{
    int antialiasing_samples_per_pixel = 10;

    // for (int y = start_y; y < end_y; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         Ray ray = camera.generate_ray(x, y, width, height);
    //         Color pixel_color = calculate_pixel_color(ray, Vector3(x, y, 0), 3);
    //         image.set_pixel(x, y, pixel_color);
    //     }
    // }

    for (int y = start_y; y < end_y; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < antialiasing_samples_per_pixel; s++)
            {
                float u = (x + static_cast<float>(rand()) / RAND_MAX) / width;
                float v = (y + static_cast<float>(rand()) / RAND_MAX) / height;
                Ray ray = camera.generate_ray(u, v, width, height);
                pixel_color += calculate_pixel_color(ray, Vector3(x, y, 0), 5);
            }
            pixel_color /= antialiasing_samples_per_pixel;
            image.set_pixel(x, y, pixel_color);
        }
    }
}