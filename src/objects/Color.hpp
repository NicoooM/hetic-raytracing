#pragma once

#include <iostream>

class Color
{
public:
  float r = 0;
  float b = 0;
  float g = 0;

  Color();
  Color(float r, float g, float b);

  Color& operator+=(const Color& other);
  Color operator/(float scalar) const;

  float R() const;
  float G() const;
  float B() const;

  Color operator+(Color const &col);
  Color operator*(float scalar) const;
  Color operator*(const Color& other) const;
  Color &operator=(Color const &col);
  friend std::ostream &operator<<(std::ostream &_stream, Color const &col);
};