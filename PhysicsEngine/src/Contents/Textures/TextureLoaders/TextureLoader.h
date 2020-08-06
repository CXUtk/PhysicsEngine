#pragma once
#include <string>
#include <memory>
#include "Contents/Textures/Texture2D.h"


class TextureLoader {
public:
    TextureLoader() = default;
    virtual ~TextureLoader() = 0 {}
    virtual std::shared_ptr<Texture2D> loadImage(const std::string& name) = 0;

    static std::unique_ptr<TextureLoader> makeTextureLoader(const std::string& name);
};
