#pragma once
#include "ShaderData.h"
#include <glm/glm.hpp>

class SpriteShaderData : public ShaderData {
public:
    SpriteShaderData(int id);

    void setColor(const glm::vec3& color) { _color = color; }
    void setProjectionMatrix(const glm::mat4& proj) { _projection = proj; }
    void setViewMatrix(const glm::mat4& view) { _view = view; }
    void setModelMatrix(const glm::mat4& model) { _model = model; }

    void apply() override;

private:
    glm::vec3 _color;
    glm::mat4 _projection, _view, _model;
};
