#pragma once
#include <string>
#include <map>
#include <memory>

#include "ShaderData/ShaderData.h"
#include "ShaderData/SpriteShaderData.h"

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    std::shared_ptr<SpriteShaderData> getSpriteShader(const std::string& name) { return _spriteShaders[name]; }

    void update(float delta);

private:
    std::map<std::string, std::shared_ptr<SpriteShaderData>> _spriteShaders;
};
