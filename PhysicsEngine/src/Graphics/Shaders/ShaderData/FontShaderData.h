#pragma once
#include "ShaderData.h"
#include <glm/glm.hpp>

class FontShaderData : public ShaderData {
public:
    FontShaderData();
    ~FontShaderData() override;

    void SetTextColor(const glm::vec3& color);
    void apply() override;

private:
    glm::vec3 _color;
};
