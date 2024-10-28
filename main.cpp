#include "Color.hpp"
#include "Image.hpp"

int main()
{
  Color red(1, 0, 0);
  Color black;

  Image image(512, 512, black);

  for (int y = 0; y < 512; y++)
  {
    for (int x = 0; x < 512; x++)
    {
      int centerX = 256;
      int centerY = 256;
      int radius = 100;
      int dx = x - centerX;
      int dy = y - centerY;
      
      if (dx * dx + dy * dy <= radius * radius)
      {
        image.SetPixel(x, y, red);
      } else
      {
        float gradient = y / 512.0;
        std::cout << "gradient: " << gradient << std::endl;
        image.SetPixel(x, y, Color(0, 0, gradient));
      }
    }
  }

  image.WriteFile("test.png");
}