#include "ShaderManager.h"

ShaderManager::ShaderManager() {
    _defaultShader = std::make_shared<DefaultShaderData>();
    _fontShader = std::make_shared<FontShaderData>();
    _circleShader = std::make_shared<CircleShaderData>();
}

ShaderManager::~ShaderManager() {
}
