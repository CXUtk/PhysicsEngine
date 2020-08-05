#include "CircleShaderData.h"
#include "Main/Game.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static std::string circlePathV = "Resources/Shaders/font.vert";
static std::string circlePathF = "Resources/Shaders/circle.frag";

CircleShaderData::CircleShaderData() :
    ShaderData(ShaderData::loadShaderProgram(circlePathV, circlePathF)), _color(glm::vec3(1)) {
}

CircleShaderData::~CircleShaderData() {
}

void CircleShaderData::apply() {
    ShaderData::apply();
    glUniform3f(glGetUniformLocation(getID(), "uColor"), _color.r, _color.g, _color.b);
    glUniformMatrix4fv(glGetUniformLocation(getID(), "projection"), 1, false, glm::value_ptr(Game::GetInstance().getProjectionMatrix()));
}
