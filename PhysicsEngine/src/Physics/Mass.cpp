
#include "Mass.h"
#include <glad/glad.h>


Mass::Mass(const glm::vec2& pos, float mass, bool fixed) : _mass(mass) {
    _pos = pos;
    _fixed = fixed;
}

Mass::~Mass() {
}

void Mass::update(float delta, const Physics* physics) {
    if (_fixed) return;
    _velocity += _force / _mass * delta;
    //_velocity *= std::pow(_damping, delta);
    _pos += _velocity * delta;
    _force = glm::vec2(0);
}

void Mass::draw(float delta, const Physics* physics) {

}
