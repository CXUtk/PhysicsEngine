#pragma once
#include <memory>
#include <string>
#include <map>
#include "Texture2D.h"
class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    std::shared_ptr<Texture2D> getTexture(const std::string& name) {
        return _textureMap[name];
    }
private:
    std::map<std::string, std::shared_ptr<Texture2D>> _textureMap;
};
