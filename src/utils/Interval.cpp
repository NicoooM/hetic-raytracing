#include <iostream>
#include "Interval.hpp"
#include <cmath>

Interval::Interval() : min(0), max(0)
{
}

Interval::Interval(float iMin, float iMax) : min(iMin), max(iMax)
{
}

Interval::~Interval()
{
}

float Interval::Min() const
{
  return min;
}

float Interval::Max() const
{
  return max;
}

float Interval::Size() const
{
  return max - min;
}

bool Interval::Contains(double value) const
{
  return value >= min && value <= max;
}

bool Interval::Surrounds(double value) const
{
  return value > min && value < max;
}

Interval &Interval::operator=(Interval const &interval)
{
  min = interval.min;
  max = interval.max;
  return *this;
}

std::ostream &operator<<(std::ostream &stream, Interval const &interval)
{
  return stream << "Interval(" << interval.min << "," << interval.max << ")";
}