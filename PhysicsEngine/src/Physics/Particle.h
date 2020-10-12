#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class Particle : public Object {
public:
    Particle();
    Particle(glm::vec2 pos, float mass, bool fixed);
    ~Particle();

    glm::vec2 centric() const override { return _pos; }
    AABB getBoundingBox()const override { return AABB(_pos, _pos); }
    void update(float delta);
    void draw(float delta);
    void addForce(glm::vec2 force) { _force += force; }

    glm::vec2 getVelocity() const { return _velocity; }
    glm::vec2 getPosition() const { return _pos; }
    bool isFixed() const { return _fixed; }
    float getMass() const { return _mass; }

    void setFixed(bool value) { _fixed = value; }
    void setPosition(glm::vec2 pos) { _pos = pos; }

private:
    bool _fixed;
    float _mass;

    float _damping;
    float _rotation;

    glm::vec2 _pos;
    glm::vec2 _force;
    glm::vec2 _velocity;
    glm::vec3 _color;
};
