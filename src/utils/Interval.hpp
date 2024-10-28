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

    float Size() const;
    bool Contains(double value) const;
    bool Surrounds(double value) const;

    Interval &operator=(Interval const &interval);
    friend std::ostream &operator<<(std::ostream &stream, Interval const &interval);
};