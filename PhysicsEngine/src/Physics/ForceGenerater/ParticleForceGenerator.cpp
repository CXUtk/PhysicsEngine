#include "ParticleForceGenerator.h"


void SpringForceGenerator::applyForce(Particle* particle, float dt) {
    if (particle->isFixed())return;
    particle->addForce(getForce(particle, _m2));
}

glm::vec2 SpringForceGenerator::getForce(const Particle* p1, const Particle* p2) const {
    float dis = glm::length(p2->getPosition() - p1->getPosition());
    glm::vec2 n = glm::normalize(p2->getPosition() - p1->getPosition());
    return n * (dis - _restLength) * (*_elasticity);
}

void GravityForceGenerator::applyForce(Particle* particle, float dt) {
    if (particle->isFixed()) return;
    particle->addForce(_gravity);
}

void DragForceGenerator::applyForce(Particle* particle, float dt) {
    if (particle->isFixed()) return;
    particle->addForce(-particle->getVelocity() * _k);
}

void SpringForceImplicitGenerator::applyForce(Particle* particle, float dt) {
    float e = *_elasticity;
    float damping = 1;
    float gamma = 0.5f * std::sqrt(4 * e - damping);
    glm::vec2 unit = glm::normalize(particle->getPosition() - _m2->getPosition());
    glm::vec2 dir = particle->getPosition() - _m2->getPosition() - unit * _restLength;
    glm::vec2 c = dir * (damping / (2 * gamma)) + particle->getVelocity() * (1 / gamma);

    glm::vec2 target = dir * cos(gamma * dt) + c * sin(gamma * dt);
    target *= exp(-0.5f * dt * damping);
    glm::vec2 acc = (target - dir) * (1 / dt / dt) - particle->getVelocity() * (1 / dt);
    particle->addForce(acc / particle->getMass());
}
