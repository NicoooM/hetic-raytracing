#include "Color.hpp"
#include "Image.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"
#include "Scene.hpp"

int main()
{
  // Setup scene
  Camera camera(Vector3(0, 0, 0));
  Scene scene(512, 512, camera);

  // Add objects
  Sphere sphere(Vector3(0, 10, 3), 2, Color(1.0, 0.0, 0.0));
  scene.add_object(sphere);

  // Add lights
  // Light light1(Vector3(2, 1.5, -1), Color(1.0, 0.7, 0.4), 2);
  Light light2(Vector3(-1.5, -0.5, -0.8), Color(0.4, 0.5, 1.0), 1.2);

  // scene.add_light(light1);
  scene.add_light(light2);

  // Render and save
  Image renderedImage = scene.render();
  renderedImage.write_file("ball.png");

  return 0;
}
