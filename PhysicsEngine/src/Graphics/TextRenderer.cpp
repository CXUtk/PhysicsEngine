#include "TextRenderer.h"
#include <iostream>
#include <algorithm>
#include "Main/Game.h"


TextRenderer::TextRenderer() {

}

TextRenderer::~TextRenderer() {
}

void TextRenderer::drawText(glm::vec2 pos, const std::string& text, float scale) const {
    auto fontManager = Game::GetInstance().getFontManager();
    auto defaultFont = fontManager->getFont("default");
    for (const auto c : text) {
        Character chr = (*defaultFont)[c];
        glm::vec2 bottomLeft = glm::vec2(pos.x + chr.Bearing.x * scale,
            pos.y - (chr.Size.y - chr.Bearing.y) * scale);
        glm::vec2 size = glm::vec2(chr.Size) * scale;

        glBindTexture(GL_TEXTURE_2D, chr.TextureID);

        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);

        // 左上角
        glTexCoord2f(0, 0);
        glVertex2f(bottomLeft.x, bottomLeft.y + size.y);

        // 左下角
        glTexCoord2f(0, 1);
        glVertex2f(bottomLeft.x, bottomLeft.y);

        // 右下角
        glTexCoord2f(1, 1);
        glVertex2f(bottomLeft.x + size.x, bottomLeft.y);

        // 右上角
        glTexCoord2f(1, 0);
        glVertex2f(bottomLeft.x + size.x, bottomLeft.y + size.y);



        glEnd();
        glDisable(GL_TEXTURE_2D);

        pos.x += chr.Advance / 64.0f;
    }
}

glm::ivec2 TextRenderer::measureString(const std::string& font, const std::string& text, float scale) const {
    glm::ivec2 result = glm::ivec2(0);
    auto fontManager = Game::GetInstance().getFontManager();
    std::shared_ptr<Font> defaultFont = fontManager->getFont("default");
    for (const auto c : text) {
        Character chr = (*defaultFont)[c];
        result.y = std::max(result.y, chr.Size.y);
        result.x += chr.Advance / 64;
    }
    return result;
}

TextRenderer& TextRenderer::getInstance() {
    static TextRenderer instance;
    return instance;
}
