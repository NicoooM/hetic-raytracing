#pragma once
#include <string>
#include <sstream>
#include "Scene.hpp"
#include "../raymath/Vector3.hpp"
#include "Color.hpp"

class SceneLoader
{
public:
    static Scene loadFromFile(const std::string &filename);

private:
    static Vector3 parseVector3(std::istringstream &iss);
    static Color parseColor(std::istringstream &iss);
    static void skipComments(std::ifstream &file);
    static std::string readNextLine(std::ifstream &file);
    static Camera parseCamera(std::ifstream &file);
    static Plan parsePlan(std::ifstream &file);
    static Light parseLight(std::ifstream &file);
    static Shape *parseShape(std::ifstream &file, const std::string &type);
};