#include <iostream>
#include <vector>

#include "Sphere.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Cube.hpp"

int main()
{
  Camera camera(Vector3(0, 0, 0), 45);
  Scene scene(1920, 1080, camera);

  // Add objects
  Sphere *sphere1 = new Sphere(Vector3(1.5, 0, 6), 1, Color(0.0, 1.0, 0.0));
  Sphere *sphere2 = new Sphere(Vector3(-1.5, 0, 6), 1, Color(1.0, 0.0, 0.0));
  Sphere *sphere3 = new Sphere(Vector3(-1.2, 0, 8), 1, Color(0.0, 0.0, 1.0));

  Cube *cube1 = new Cube(Vector3(0, 0, 8), 2, Color(0.0, 0.0, 1.0));

  scene.add_object(cube1);
  scene.add_object(sphere1);
  scene.add_object(sphere2);
  scene.add_object(sphere3);

  Plan default_plan(Vector3(0, -10, 0), Vector3(0, 1, 0));
  scene.add_plan(default_plan);

  Light light(Vector3(1.2, 2, 0), Color(1.0, 1.0, 1.0), 1.5);
  Light light2(Vector3(-1.5, -0.5, -0.8), Color(0.4, 0.5, 1.0), 1.2);
  scene.add_light(light);
  scene.add_light(light2);

  Image renderedImage = scene.render();
  renderedImage.write_file("ball.png");

  // Delete objects for performance
  delete sphere1;
  delete sphere2;

  return 0;
}
