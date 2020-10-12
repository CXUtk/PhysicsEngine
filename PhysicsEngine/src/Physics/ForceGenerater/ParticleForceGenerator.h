#pragma once
#include "Physics/Particle.h"
#include <memory>

class ParticleForceGenerator {
public:
    virtual void applyForce(Particle* particle, float dt) = 0;
};


class GravityForceGenerator : public ParticleForceGenerator {
public:
    GravityForceGenerator(glm::vec2 gravity) :_gravity(gravity) {}
    void applyForce(Particle* particle, float dt) override;
private:
    glm::vec2 _gravity;
};

class SpringForceGenerator : public ParticleForceGenerator {
public:
    SpringForceGenerator(Particle* m2, float* K, float restLen) : _m2(m2), _elasticity(K), _restLength(restLen) {}
    void applyForce(Particle* particle, float dt) override;
    glm::vec2 getForce(const Particle* p1, const Particle* p2) const;

private:
    Particle* _m2;
    float _restLength;
    float* _elasticity;
};


class DragForceGenerator : public ParticleForceGenerator {
public:
    DragForceGenerator(float k) : _k(k) {}
    void applyForce(Particle* particle, float dt) override;

private:
    float _k;
};


class SpringForceImplicitGenerator : public ParticleForceGenerator {
public:
    SpringForceImplicitGenerator(Particle* m2, float* K, float restLen) : _m2(m2), _elasticity(K), _restLength(restLen) {}
    void applyForce(Particle* particle, float dt) override;

private:
    Particle* _m2;
    float _restLength;
    float* _elasticity;
};
