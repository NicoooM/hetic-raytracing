#pragma once

#include <iostream>

class Color
{
private:
  float r = 0;
  float b = 0;
  float g = 0;

public:
  Color();
  Color(float r, float g, float b);
  ~Color();

  float R() const;
  float G() const;
  float B() const;

  Color operator+(Color const &col);
  Color operator*(float scalar) const;
  Color operator*(const Color& other) const;
  Color &operator=(Color const &col);
  Color& operator+=(const Color& other);
  Color operator/(float scalar) const;
  Color& operator/=(float scalar) {
    r /= scalar;
    g /= scalar;
    b /= scalar;
    return *this;
  }
  friend std::ostream &operator<<(std::ostream &_stream, Color const &col);
};