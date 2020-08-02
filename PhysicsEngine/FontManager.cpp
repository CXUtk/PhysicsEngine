#include "FontManager.h"
#include <iostream>

FontManager::FontManager() {
    auto loader = FontLoader::makeLoader(FontLoaderType::FreeType);
    _fontMap["default"] = loader->loadFont("Fonts/arial.ttf", 32);
}

FontManager::~FontManager() {
    std::cout << "FontManager has been released" << std::endl;
}
