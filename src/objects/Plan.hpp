#pragma once


#include "../raymath/Vector3.hpp"

class Plan
{
private:
    Vector3 point;  // Remplacez Vector3 par le type de votre choix
    Vector3 normal; // Remplacez Vector3 par le type de votre choix

public:
    Plan(const Vector3& point, const Vector3& normal);
    ~Plan();

    // Ajoutez des méthodes pour accéder et modifier le point et la normale si nécessaire
    const Vector3& getPoint() const;
    const Vector3& getNormal() const;
    void setPoint(const Vector3& point);
    void setNormal(const Vector3& normal);
};
