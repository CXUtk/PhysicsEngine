#include "SpriteShaderData.h"
#include "Main/Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SpriteShaderData::SpriteShaderData(int id) :ShaderData(id) {
    _color = glm::vec3(1);
    _projection = glm::identity<glm::mat4>();
    _view = glm::identity<glm::mat4>();
    _model = glm::identity<glm::mat4>();
}


void SpriteShaderData::apply() {
    ShaderData::apply();
    glUniform3f(glGetUniformLocation(getID(), "uColor"), _color.r, _color.g, _color.b);
    glUniformMatrix4fv(glGetUniformLocation(getID(), "projection"), 1, false, glm::value_ptr(_projection));
    glUniformMatrix4fv(glGetUniformLocation(getID(), "view"), 1, false, glm::value_ptr(_view));
    glUniformMatrix4fv(glGetUniformLocation(getID(), "model"), 1, false, glm::value_ptr(_model));
}
