#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include <memory>

#include "Contents/Fonts/Font.h"
class FontManager {
public:
    FontManager();
    ~FontManager();

    std::shared_ptr<Font> getFont(const std::string& name) {
        return _fontMap[name];
    }

private:
    std::map<std::string, std::shared_ptr<Font>> _fontMap;
};
