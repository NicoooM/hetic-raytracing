#include <iostream>
#include "SceneLoader.hpp"

int main()
{
  try
  {
    Scene scene = SceneLoader::loadFromFile("scene.txt");
    Image renderedImage = scene.render();
    renderedImage.write_file("ball.png");
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
