#pragma once
#include "Particle.h"
class Particle;
class ParticleForceGenerator {
public:
    virtual void applyForce(Particle* particle, float dt) = 0;
};


class GravityForceGenerator : public ParticleForceGenerator {
public:
    GravityForceGenerator(glm::vec2 gravity) :_gravity(gravity) {}
    void applyForce(Particle* particle, float dt) override;
    glm::vec2 _gravity;
};

class SpringForceGenerator : public ParticleForceGenerator {
public:
    SpringForceGenerator(Particle* m2, float K, float restLen) : _m2(m2), _elasticity(K), _restLength(restLen) {}
    void applyForce(Particle* particle, float dt) override;
    Particle* _m2;
    float _restLength;
    float _elasticity;
};


class DragForceGenerator : public ParticleForceGenerator {
public:
    DragForceGenerator(float k1, float k2) :_k1(k1), _k2(k2) {}
    void applyForce(Particle* particle, float dt) override;
    float _k1, _k2;
};
