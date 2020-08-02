#include "ParticleForceGenerator.h"


glm::vec2 getForce(const glm::vec2& a, const glm::vec2& b, const SpringForceGenerator& s) {
    float dis = glm::length(b - a);
    glm::vec2 n = glm::normalize(b - a);
    return n * (dis - s._restLength) * s._elasticity;
}

void SpringForceGenerator::applyForce(Particle* particle, float dt) {
    if (particle->_fixed)return;
    particle->addForce(getForce(particle->_pos, _m2->_pos, *this));
}

void GravityForceGenerator::applyForce(Particle* particle, float dt) {
    if (particle->_fixed) return;
    particle->addForce(_gravity);
}

void DragForceGenerator::applyForce(Particle* particle, float dt) {
    float f = std::pow(_k1, dt);
    particle->addForce(-particle->_velocity * _k1);
}
