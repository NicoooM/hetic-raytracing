#include "Color.hpp"
#include "Image.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

int main()
{
  Color red(1, 0, 0);
  Color black;

  Image image(512, 512, black);
  Sphere sphere(Vector3(0, 0, 3), 1.5, red);

  Vector3 cameraOrigin(0, 0, 0);

  for (int y = 0; y < 512; y++)
  {
    for (int x = 0; x < 512; x++)
    {
      Vector3 pixelPosition(
          (x - 256) / 100.0,
          (y - 256) / 100.0,
          1.0);

      Vector3 rayDirection = (pixelPosition - cameraOrigin).normalize();
      Ray ray(cameraOrigin, rayDirection);

      if (ray.is_intersecting(sphere))
      {
        Vector3 hitPoint = ray.hit_sphere(sphere);
        std::cout << "Hit point at (" << x << "," << y << "): " << hitPoint << std::endl;
        Vector3 normal = (hitPoint - sphere.get_center()).normalize();
        
        Color normalMapColor(
          (normal.get_x() + 1.0f) * 0.5f,  
          (normal.get_y() + 1.0f) * 0.5f,  
          (normal.get_z() + 1.0f) * 0.5f   
        );
        
        std::cout << "Normal Map Color at (" << x << "," << y << "): R=" << normalMapColor.R() 
                  << " G=" << normalMapColor.G() 
                  << " B=" << normalMapColor.B() << std::endl;

        image.set_pixel(x, y, normalMapColor);
      }
      else
      {
        float gradient = static_cast<float>(y) / 512.0f;
        image.set_pixel(x, y, Color(0, 0, gradient));
      }
    }
  }

  image.write_file("test.png");

  return 0;
}
