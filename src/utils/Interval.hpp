#pragma once

#include <iostream>

class Interval
{
private:
    float min;
    float max;

public:
    Interval();
    Interval(float min, float max);
    ~Interval();

    float Min() const;
    float Max() const;

    bool Contains(float value) const;
    bool Contains(Interval interval) const;
    bool Overlaps(Interval interval) const;
    Interval Intersection(Interval interval) const;
    Interval Union(Interval interval) const;

    Interval &operator=(Interval const &interval);
    friend std::ostream &operator<<(std::ostream &stream, Interval const &interval);
};