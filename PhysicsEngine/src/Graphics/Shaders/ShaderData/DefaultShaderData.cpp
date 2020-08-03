#include "DefaultShaderData.h"
#include "Main/Game.h"
#include <glm/gtc/type_ptr.hpp>

static std::string defaultPathV = "Resources/Shaders/default.vert";
static std::string defaultPathF = "Resources/Shaders/default.frag";

DefaultShaderData::DefaultShaderData() : ShaderData(ShaderData::loadShaderProgram(defaultPathV, defaultPathF)), _color(glm::vec3(1)) {

}

void DefaultShaderData::apply() {
    ShaderData::apply();
    glUniform3f(glGetUniformLocation(getID(), "uColor"), _color.r, _color.g, _color.b);
    glUniformMatrix4fv(glGetUniformLocation(getID(), "projection"), 1, false, glm::value_ptr(Game::GetInstance().getProjectionMatrix()));
}
