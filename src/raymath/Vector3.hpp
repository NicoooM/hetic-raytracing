#pragma once

#include <iostream>

class Vector3
{
private:
    float x = 0;
    float y = 0;
    float z = 0;

public:
    Vector3();
    Vector3(float x, float y, float z);
    ~Vector3();

    float X() const;
    float Y() const;
    float Z() const;

    Vector3 Normalize() const;
    float DotProduct(Vector3 const &vec) const;
    Vector3 Projection(Vector3 const &vec) const;
    float Pythagorean() const;
    // Vector3 Reflect(Vector3 const &normal) const;

    Vector3 operator*(float const &val) const;
    Vector3 operator+(Vector3 const &vec) const;
    Vector3 operator-(Vector3 const &vec) const;
    Vector3 &operator=(Vector3 const &vec);

    friend std::ostream &operator<<(std::ostream &stream, Vector3 const &vec);
};