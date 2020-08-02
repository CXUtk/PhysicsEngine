#pragma once
#include "Scene.h"
#include "Physics.h"
#include <vector>
#include "Mass.h"

constexpr int MAX_MASSES = 1005;

class MassSpringScene : public Scene {
public:
    MassSpringScene();
    ~MassSpringScene() override;

    void simulate(float delta);
    void update(float delta);
    void draw(float delta);

private:
    int _groundY;
    std::vector<Mass> _masses;
    std::vector<int> _adjancent[MAX_MASSES];
    Physics* _physics;
};
