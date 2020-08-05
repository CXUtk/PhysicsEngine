#include "TextureManager.h"
#include "TextureLoaders/TextureLoader.h"

TextureManager::TextureManager() {
    auto textureLoader = TextureLoader::makeTextureLoader("stbi");

    auto texture = textureLoader->loadImage("Resources/Textures/Icon.png");
    _textureMap["icon"] = texture;
}

TextureManager::~TextureManager() {
}
