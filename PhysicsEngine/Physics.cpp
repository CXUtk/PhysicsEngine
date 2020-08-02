#include "Physics.h"
#include "ParticleForceGenerator.h"


Physics::Physics(const PhysicsConfig& config) :_config(config) {
    _gravityGenerator = new GravityForceGenerator(config.gravity);
}

void Physics::addGravity(Particle* particle) {
    registerForce(particle, _gravityGenerator);
}

void Physics::registerForce(Particle* particle, ParticleForceGenerator* forceGen) {
    this->_forceRegs.push_back({ particle, forceGen });
}

void Physics::removeForce(Particle* particle, ParticleForceGenerator* forceGen) {
    // Not implemented
}

void Physics::updateForces(float dt) {
    for (auto& force : _forceRegs) {
        force.forceGen->applyForce(force.particle, dt);
    }
}
