#pragma once
#include "Physics.h"
class Physics;
class Particle : public Object {
public:
    Particle();
    ~Particle();

    virtual glm::vec2 centric() const = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual void update(float delta, const Physics* physics) = 0;
    virtual void draw(float delta, const Physics* physics) = 0;
    void addForce(glm::vec2 force) { _force += force; }

    bool _fixed;
    float _damping;

    float _rotation;
    glm::vec2 _pos;
    glm::vec2 _force;
    glm::vec2 _velocity;
    glm::vec3 _color;
};
