#include "SceneLoader.hpp"
#include <fstream>
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Plan.hpp"

Scene SceneLoader::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    Camera camera(Vector3(0, 0, 0), 45);
    int width = 1920, height = 1080;
    Scene *scene = nullptr;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "CAMERA")
        {
            camera = parseCamera(file);
        }
        else if (token == "RESOLUTION")
        {
            iss >> width >> height;
            if (!scene)
            {
                scene = new Scene(width, height, camera);
            }
        }
        else if (token == "LIGHT")
        {
            if (!scene)
            {
                scene = new Scene(width, height, camera);
            }
            scene->add_light(parseLight(file));
        }
        else if (token == "PLAN")
        {
            if (!scene)
            {
                scene = new Scene(width, height, camera);
            }
            scene->add_plan(parsePlan(file));
        }
        else if (token == "SPHERE" || token == "CUBE")
        {
            if (!scene)
            {
                scene = new Scene(width, height, camera);
            }
            Shape *obj = parseShape(file, token);
            if (obj)
            {
                scene->add_object(obj);
            }
        }
    }

    if (!scene)
    {
        scene = new Scene(width, height, camera);
    }

    Scene finalScene = *scene;
    delete scene;
    return finalScene;
}

Vector3 SceneLoader::parseVector3(std::istringstream &iss)
{
    float x, y, z;
    iss >> x >> y >> z;
    return Vector3(x, y, z);
}

Color SceneLoader::parseColor(std::istringstream &iss)
{
    float r, g, b;
    iss >> r >> g >> b;
    return Color(r, g, b);
}

std::string SceneLoader::readNextLine(std::ifstream &file)
{
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        return line;
    }
    return "";
}

Camera SceneLoader::parseCamera(std::ifstream &file)
{
    Vector3 position(0, 0, 0);
    float fov = 45;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line == "end")
            break;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "position")
        {
            position = parseVector3(iss);
        }
        else if (token == "fov")
        {
            iss >> fov;
        }
    }

    return Camera(position, fov);
}

Plan SceneLoader::parsePlan(std::ifstream &file)
{
    Vector3 position(0, 0, 0);
    Vector3 normal(0, 1, 0);
    Color color(1, 1, 1);

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line == "end")
            break;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "position")
        {
            position = parseVector3(iss);
        }
        else if (token == "normal")
        {
            normal = parseVector3(iss);
        }
    }

    return Plan(position, normal);
}

Light SceneLoader::parseLight(std::ifstream &file)
{
    Vector3 position(0, 0, 0);
    Color color(1, 1, 1);
    float intensity = 1.0;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line == "end")
            break;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "position")
        {
            position = parseVector3(iss);
        }
        else if (token == "color")
        {
            color = parseColor(iss);
        }
        else if (token == "intensity")
        {
            iss >> intensity;
        }
    }

    return Light(position, color, intensity);
}

Shape *SceneLoader::parseShape(std::ifstream &file, const std::string &type)
{
    Vector3 position(0, 0, 0);
    Color color(1, 1, 1);
    float radius = 1.0; // for sphere
    float size = 1.0;   // for cube

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        if (line == "end")
            break;

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "position")
        {
            position = parseVector3(iss);
        }
        else if (token == "color")
        {
            color = parseColor(iss);
        }
        else if (token == "radius")
        {
            iss >> radius;
        }
        else if (token == "size")
        {
            iss >> size;
        }
    }

    if (type == "SPHERE")
    {
        return new Sphere(position, radius, color);
    }
    else if (type == "CUBE")
    {
        return new Cube(position, size, color);
    }

    return nullptr;
}