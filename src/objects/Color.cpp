#include <iostream>
#include "Color.hpp"
#include <cmath>


Color:: Color() : r(0), b(0), g(0)
{  
}

Color:: Color(float iR, float iG, float iB) : r(iR), g(iG), b(iB)
{  
}

Color::~ Color()
{
}

float Color::R() const
{
  return r;
}

float Color::G() const
{
  return g;
}

float Color::B() const
{
  return b;
}

/**
 * Implementation of the + operator :
 * Adding two colors is done by just adding the different components together :
 * (r1, g1, b1) + (r2, g2, b2) = (r1 + r2, g1 + g2, b1 + b2)
 */
Color Color::operator+(Color const& col) {
  Color c;
  c.r = fmax(fmin(r + col.r, 1), 0);
  c.g = fmax(fmin(g + col.g, 1), 0);
  c.b = fmax(fmin(b + col.b, 1), 0);
  return c;
}

/**
 * Overriding the assignment operator
 */
Color& Color::operator=(Color const& col) {
  r = col.r;
  g = col.g;
  b = col.b;
  return *this;
}

Color Color::operator*(float scalar) const {
    return Color(R() * scalar, G() * scalar, B() * scalar);
}

Color Color::operator*(const Color& other) const {
    return Color(R() * other.R(), G() * other.G(), B() * other.B());
}

/**
 * Here we implement the << operator :
 * We take each component and append it to he stream, giving it a nice form on the console
 */
std::ostream & operator<<(std::ostream & _stream, Color const & col) {  
  return _stream << "(" << col.r << "," << col.g << "," << col.b << ")";
}