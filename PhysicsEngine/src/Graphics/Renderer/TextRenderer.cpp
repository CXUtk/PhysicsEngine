#include "TextRenderer.h"
#include <iostream>
#include <algorithm>
#include "Main/Game.h"



TextRenderer::TextRenderer() {
    // 不会变的顶点列表
    unsigned int indices[] = {
        0, 1, 3,
        0, 2, 1,
    };

    // 准备绘制一个Quad需要的顶点缓存序列
    // 一个Quad由4个顶点和两个三角形组成
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);


    glBindVertexArray(_vao);

    // 绑定VAO到四个顶点
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 4, nullptr, GL_DYNAMIC_DRAW);

    // 绑定顶点序列到indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);

    // 解除当前绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _fontShader.reset(new FontShaderData());
}

TextRenderer::~TextRenderer() {
}

void TextRenderer::drawText(glm::vec2 pos, const std::string& text, float scale, const glm::vec3& color) {
    _fontShader->SetTextColor(color);
    _fontShader->apply();

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

TextRenderer& TextRenderer::getInstance() {
    static TextRenderer instance;
    return instance;
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
