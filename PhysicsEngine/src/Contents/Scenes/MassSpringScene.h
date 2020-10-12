#pragma once
#include "Scene.h"
#include "Physics/Physics.h"
#include <vector>

constexpr int MAX_MASSES = 1005;

class MassSpringScene : public Scene {
public:
    MassSpringScene();
    ~MassSpringScene() override;

    void simulate(float delta);
    void update(float delta) override;
    void draw(float delta) override;

private:
    int _groundY;
    std::vector<std::shared_ptr<Particle>> _masses;
    std::vector<int> _adjancent[MAX_MASSES];
    std::shared_ptr<Physics> _physics;
    std::shared_ptr<ParticleForceGenerator> _gravityGenerater;
    std::shared_ptr<ParticleForceGenerator> _dragGenerater;

    std::shared_ptr<Particle> _selectedParticle;

    std::shared_ptr<Particle> makeNode(glm::vec2 pos, bool fixed, const std::vector<std::shared_ptr<Particle>>& links);
};
