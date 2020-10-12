#include "Physics.h"
#include "Physics/ForceGenerater/ParticleForceGenerator.h"


Physics::Physics(const PhysicsConfig& config) :_config(config) {
}

Physics::~Physics() {
}


void Physics::registerForce(Particle* particle, std::shared_ptr<ParticleForceGenerator> forceGen) {
    ForceRegisteration forceR;
    forceR.particle = particle;
    forceR.forceGen = forceGen;
    this->_forceRegs.emplace_back(forceR);
}

void Physics::removeForce(Particle* particle, std::shared_ptr<ParticleForceGenerator> forceGen) {
}

void Physics::updateForces(float dt) {
    for (auto& force : _forceRegs) {
        force.forceGen->applyForce(force.particle, dt);
    }
}
