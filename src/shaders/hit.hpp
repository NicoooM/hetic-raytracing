#pragma once

#include "../raymath/Vector3.hpp"

class Hit {
private:
    bool hasHit;    // Boolen pour dire si collision ou pas 
    float distance; // Distance jusqu'au point d'intersection
    Vector3 point;  // Point d'intersection
    Vector3 normal; // Normale à la surface au point d'intersection

public:
    Hit() : hasHit(false), distance(0), point(Vector3()), normal(Vector3()) {}
    Hit(float d, Vector3 p, Vector3 n) : 
        hasHit(true), 
        distance(d), 
        point(p), 
        normal(n) {}

    ~Hit() = default;

    // Accesseurs
    bool HasCollision() const { return hasHit; }
    float Distance() const { return distance; }
    Vector3 Point() const { return point; }
    Vector3 Normal() const { return normal; }

    // Méthode statique pour le cas ou ya un Hit sans collision
    static Hit NoHit() {
        return Hit();
    }
};

