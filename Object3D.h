class Object3D {
protected:
    // Position de l'objet
    float x, y, z;

public:
    Object3D(float x = 0, float y = 0, float z = 0) 
        : x(x), y(y), z(z) {}
    
    virtual ~Object3D() = default;

    // Méthode virtuelle pure que les classes dérivées devront implémenter
    virtual void draw() = 0;

    // Getters et setters pour la position
    void setPosition(float newX, float newY, float newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }
}; 