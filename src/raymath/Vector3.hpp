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

    float get_x() const;
    float get_y() const;
    float get_z() const;

    Vector3 normalize() const;
    float dot_product(Vector3 const &vec) const;
    float pythagorean() const;

    Vector3 operator*(float const &val) const;
    Vector3 operator+(Vector3 const &vec) const;
    Vector3 operator-(Vector3 const &vec) const;
    Vector3 &operator=(Vector3 const &vec);
    friend Vector3 operator*(float scalar, const Vector3& vec);
    friend std::ostream &operator<<(std::ostream &stream, Vector3 const &vec);
};
