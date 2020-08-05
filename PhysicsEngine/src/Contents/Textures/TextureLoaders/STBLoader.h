#pragma once
#include <stb_image.h>
#include "TextureLoader.h"

class STBLoader : public TextureLoader {
public:
    STBLoader();
    ~STBLoader() override;
    std::shared_ptr<Texture2D> loadImage(const std::string& name) override;
};
