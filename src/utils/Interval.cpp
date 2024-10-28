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

bool Interval::Contains(float value) const
{
  return value >= min && value <= max;
}

bool Interval::Contains(Interval interval) const
{
  return interval.min >= min && interval.max <= max;
}

bool Interval::Overlaps(Interval interval) const
{
  return interval.min <= max && interval.max >= min;
}

Interval Interval::Intersection(Interval interval) const
{
  float newMin = std::max(min, interval.min);
  float newMax = std::min(max, interval.max);
  return Interval(newMin, newMax);
}

Interval Interval::Union(Interval interval) const
{
  float newMin = std::min(min, interval.min);
  float newMax = std::max(max, interval.max);
  return Interval(newMin, newMax);
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
