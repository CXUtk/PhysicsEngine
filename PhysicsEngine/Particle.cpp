#include "Particle.h"
#include <GLFW/glfw3.h>

Particle::Particle() : _fixed(false), _damping(0.1f), _rotation(0), _pos(glm::vec2(0)), _force(glm::vec2(0))
, _velocity(glm::vec2(0)), _color(glm::vec3(1)) {

}

Particle::~Particle() {
}
