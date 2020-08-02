#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "Object.h"
#include "ParticleForceGenerator.h"


class Particle;
class ParticleForceGenerator;
class GravityForceGenerator;

struct PhysicsConfig {
    glm::vec2 gravity;
    int stepsPerFrame;
};

class Physics {
public:
    struct ForceRegisteration {
        Particle* particle;
        ParticleForceGenerator* forceGen;
    };
    Physics(const PhysicsConfig& config);
    ~Physics() { delete _gravityGenerator; }

    glm::vec2 getGravity()const { return _config.gravity; }
    int getStepsPerFrame() const { return _config.stepsPerFrame; }

    void addGravity(Particle* particle);
    void registerForce(Particle* particle, ParticleForceGenerator* forceGen);
    void removeForce(Particle* particle, ParticleForceGenerator* forceGen);
    void updateForces(float dt);

private:
    PhysicsConfig _config;
    std::vector<ForceRegisteration> _forceRegs;
    GravityForceGenerator* _gravityGenerator;
};
