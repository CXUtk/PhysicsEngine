#pragma once
#include <string>
#include <map>
#include <memory>

#include "ShaderData/ShaderData.h"
#include "ShaderData/DefaultShaderData.h"
#include "ShaderData/FontShaderData.h"

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    std::shared_ptr<DefaultShaderData> getDefaultShader() { return _defaultShader; }
    std::shared_ptr<FontShaderData> getFontShader() { return _fontShader; }

private:
    std::shared_ptr<DefaultShaderData> _defaultShader;
    std::shared_ptr<FontShaderData> _fontShader;
};
