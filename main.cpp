#include <iostream>
#include <vector>
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Color.hpp"

int main() {
    // Configuration de l'image
    int image_width = 512;
    int image_height = 512; 

    // Création de la scène
    Camera camera(Vector3(0, 0, 0));
    Scene scene(image_width, image_height, camera);

    // Ajout d'une sphère
    Sphere sphere(Vector3(0, 0, 3), 2, Color(1.0, 0.0, 0.0));    
    scene.add_object(sphere);

    Light light(Vector3(-1.5, -0.5, -0.8), Color(0.4, 0.5, 1.0), 1.2);  
    scene.add_light(light);

    // Rendu de la scène
    Image renderedImage = scene.render();
    renderedImage.write_file("ball.png");

    return 0;
}
