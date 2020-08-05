#include "TextureLoader.h"
#include "STBLoader.h"

std::unique_ptr<TextureLoader> TextureLoader::makeTextureLoader(const std::string& name) {
    if (name == "stbi") return std::make_unique<STBLoader>();
    else return std::unique_ptr<TextureLoader>();
}
