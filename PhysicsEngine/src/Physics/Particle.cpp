#include "Particle.h"
#include <GLFW/glfw3.h>

Particle::Particle() : _fixed(false), _damping(1.f), _rotation(0), _pos(glm::vec2(0)), _force(glm::vec2(0))
, _velocity(glm::vec2(0)), _color(glm::vec3(1)) {

}

Particle::Particle(glm::vec2 pos, float mass, bool fixed) : Particle() {
    _pos = pos;
    _mass = mass;
    _fixed = fixed;
}

Particle::~Particle() {
}

void Particle::update(float delta) {
    if (_fixed) return;
    _velocity *= exp(-delta * _damping);
    _velocity += (_force * delta) / _mass;
    _pos += _velocity * delta;
    _force = glm::vec2(0);
}

void Particle::draw(float delta) {
}
