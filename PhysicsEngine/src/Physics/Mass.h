#pragma once
#include "Particle.h"
class Mass :public Particle {
public:
    Mass(const glm::vec2& pos, float mass, bool fixed);
    ~Mass();

    glm::vec2 centric() const override { return _pos; }
    AABB getBoundingBox()const override { return AABB(_pos, _pos); }
    void update(float delta, const Physics* physics) override;
    void draw(float delta, const Physics* physics) override;


private:
    float _mass;
};
