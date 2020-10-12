#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <memory>

#include "Object.h"
#include "Physics/ForceGenerater/ParticleForceGenerator.h"

struct PhysicsConfig {
    glm::vec2 gravity;
    int stepsPerFrame;
};

class Physics {
public:
    struct ForceRegisteration {
        Particle* particle;
        std::shared_ptr<ParticleForceGenerator> forceGen;
    };
    Physics(const PhysicsConfig& config);
    ~Physics();

    glm::vec2 getGravity()const { return _config.gravity; }
    int getStepsPerFrame() const { return _config.stepsPerFrame; }

    void registerForce(Particle* particle, std::shared_ptr<ParticleForceGenerator> forceGen);
    void removeForce(Particle* particle, std::shared_ptr<ParticleForceGenerator> forceGen);
    void updateForces(float dt);

private:
    PhysicsConfig _config;
    std::vector<ForceRegisteration> _forceRegs;
};
