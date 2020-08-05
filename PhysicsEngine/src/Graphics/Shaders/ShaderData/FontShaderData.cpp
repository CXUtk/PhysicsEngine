#include "FontShaderData.h"
#include "Main/Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static std::string fontPathV = "Resources/Shaders/font.vert";
static std::string fontPathF = "Resources/Shaders/font.frag";

FontShaderData::FontShaderData() :ShaderData(ShaderData::loadShaderProgram(fontPathV, fontPathF)) {
    _color = glm::vec3(1);
}

FontShaderData::~FontShaderData() {
}

void FontShaderData::SetTextColor(const glm::vec3& color) {
    _color = color;
}

void FontShaderData::apply() {
    ShaderData::apply();
    glUniform3f(glGetUniformLocation(getID(), "textColor"), _color.r, _color.g, _color.b);
    glUniformMatrix4fv(glGetUniformLocation(getID(), "projection"), 1, false, glm::value_ptr(Game::GetInstance().getProjectionMatrix()));
}
