#include "ShaderManager.h"

ShaderManager::ShaderManager() {
    _defaultShader = std::make_shared<DefaultShaderData>();
    _fontShader = std::make_shared<FontShaderData>();
}

ShaderManager::~ShaderManager() {
}
