#include <iostream>
#include <vector>
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Color.hpp"


int main()
{
  // Setup scene
  Camera camera(Vector3(0, 0, 0), 100);
  Scene scene(1920, 1080, camera);

  // Add objects
  Sphere sphere1(Vector3(0, 0.0, 6), 1, Color(1.0, 0.0, 0.0));
  // Sphere sphere2(Vector3(-1.0, 0.0, 3.5), 0.5, Color(0.0, 1.0, 0.0));
  // Sphere sphere3(Vector3(1.0, 0.0, 3.5), 0.5, Color(0.0, 0.0, 1.0));
  // Sphere sphere4(Vector3(4.0, 0.0, 3), 0.5, Color(1.0, 1.0, 0.0));

  scene.add_object(sphere1);
  // scene.add_object(sphere2);
  // scene.add_object(sphere3);
  // scene.add_object(sphere4);

  Light light(Vector3(1.2, 2, 0), Color(1.0, 1.0, 1.0), 1.5);
  scene.add_light(light);

    // Ajout d'un rectangle pour le sol
    // Rectangle rectangle(Vector3(0, 0, 1), Color(0.0, 1.0, 0.0), 100.0, 100.0);
    // scene.add_object(rectangle);
    // Rendu de la scène
    Image renderedImage = scene.render();
    renderedImage.write_file("ball.png");

    return 0;
}
