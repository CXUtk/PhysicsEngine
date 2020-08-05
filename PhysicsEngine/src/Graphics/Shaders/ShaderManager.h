#pragma once
#include <string>
#include <map>
#include <memory>

#include "ShaderData/ShaderData.h"
#include "ShaderData/DefaultShaderData.h"
#include "ShaderData/FontShaderData.h"
#include "ShaderData/CircleShaderData.h"

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    std::shared_ptr<DefaultShaderData> getDefaultShader() { return _defaultShader; }
    std::shared_ptr<FontShaderData> getFontShader() { return _fontShader; }
    std::shared_ptr<CircleShaderData> getCircleShader() { return _circleShader; }

private:
    std::shared_ptr<DefaultShaderData> _defaultShader;
    std::shared_ptr<FontShaderData> _fontShader;
    std::shared_ptr<CircleShaderData> _circleShader;
};
