#pragma once
#include <memory>
#include <string>
#include <map>
#include "Texture2D.h"


/*
    管理图像资源的类，可以通过名字获取2D图像实例
*/
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
