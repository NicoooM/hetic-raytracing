#include "Color.hpp"
#include "Image.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector3.hpp" // Assuming you have this class for vector operations

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

      Vector3 rayDirection = (pixelPosition - cameraOrigin).Normalize();
      Ray ray(cameraOrigin, rayDirection);

      if (ray.Intersect(sphere))
      {
        image.SetPixel(x, y, red);
      }
      else
      {
        float gradient = static_cast<float>(y) / 512.0f;
        image.SetPixel(x, y, Color(0, 0, gradient));
      }
    }
  }

  image.WriteFile("test.png");

  return 0;
}
