
#include "Mass.h"
#include "TextRenderer.h"
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
    _velocity *= std::pow(_damping, delta);
    _pos += _velocity * delta;
    _force = glm::vec2(0);
}

void Mass::draw(float delta, const Physics* physics) {
    glPointSize(8);
    glColor3f(_color.r, _color.g, _color.b);

    glBegin(GL_POINTS);
    glVertex2f(_pos.x, _pos.y);
    glEnd();


}
