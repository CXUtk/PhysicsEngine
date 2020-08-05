#include "TextRenderer.h"
#include <iostream>
#include <algorithm>
#include "Main/Game.h"
#include "Graphics/GLUtils.h"


TextRenderer::TextRenderer() {
    GLUtils::genQuad(_vao, _vbo, _ebo);
}

TextRenderer::~TextRenderer() {
}

void TextRenderer::drawText(glm::vec2 pos, const std::string& text, float scale, const glm::vec3& color) {
    auto fontShader = Game::GetInstance().getShaderManager()->getSpriteShader("font");
    fontShader->setProjectionMatrix(Game::GetInstance().getProjectionMatrix());
    fontShader->setColor(color);
    fontShader->apply();

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);

    auto fontManager = Game::GetInstance().getFontManager();
    auto defaultFont = fontManager->getFont("default");

    for (const auto c : text) {
        Character chr = (*defaultFont)[c];
        glm::vec2 bottomLeft = glm::vec2(pos.x + chr.Bearing.x * scale,
            pos.y - (chr.Size.y - chr.Bearing.y) * scale);
        glm::vec2 size = glm::vec2(chr.Size) * scale;
        draw_quad(chr.TextureID, bottomLeft, size);
        pos.x += chr.Advance / 64;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
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

void TextRenderer::draw_quad(GLuint textureId, glm::vec2 bottomLeft, glm::vec2 size) {
    glm::vec4 vertices[4] = {
        // 左下角
        glm::vec4(bottomLeft, 0, 1),
        // 右上角
        glm::vec4(bottomLeft + size, 1, 0),
        // 左上角
        glm::vec4(bottomLeft + glm::vec2(0, size.y), 0, 0),
        // 右下角
        glm::vec4(bottomLeft + glm::vec2(size.x, 0), 1, 1),
    };
    // 使用贴图
    glBindTexture(GL_TEXTURE_2D, textureId);

    // 替换顶点数据到当前Quad
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 绘制Quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}
