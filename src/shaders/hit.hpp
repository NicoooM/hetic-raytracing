#pragma once

#include "../raymath/Vector3.hpp"

class Hit {
private:
    bool has_hit;   // Boolean to say if there is a collision or not 
    float distance; // Distance to the intersection point
    Vector3 point;  // Intersection point
    Vector3 normal; // Normal to the surface at the intersection point

public:
    Hit() : has_hit(false), distance(0), point(Vector3()), normal(Vector3()) {}
    
    Hit(float d, Vector3 p, Vector3 n) : 
        has_hit(true), 
        distance(d), 
        point(p), 
        normal(n) {}

    ~Hit() = default;

    bool has_collision() const { return has_hit; }
    float get_distance() const { return distance; }
    Vector3 get_point() const { return point; }
    Vector3 get_normal() const { return normal; }

    // Static method for the case where there is no collision
    static Hit no_hit() {
        return Hit();
    }
};

