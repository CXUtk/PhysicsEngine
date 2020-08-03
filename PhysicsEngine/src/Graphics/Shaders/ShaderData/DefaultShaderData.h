#pragma once
#include "ShaderData.h"
#include <glm/glm.hpp>

class DefaultShaderData : public ShaderData {
public:
    DefaultShaderData();
    ~DefaultShaderData() override {}

    void setColor(const glm::vec3& color) { _color = color; }
    void apply() override;
private:
    glm::vec3 _color;
};
