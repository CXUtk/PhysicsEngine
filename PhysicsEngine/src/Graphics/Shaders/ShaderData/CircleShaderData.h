#pragma once
#include "ShaderData.h"
#include <glm/glm.hpp>

class CircleShaderData : public ShaderData {
public:
    CircleShaderData();
    ~CircleShaderData() override;

    void setColor(const glm::vec3& color) { _color = color; }
    void apply() override;
private:
    glm::vec3 _color;
};
