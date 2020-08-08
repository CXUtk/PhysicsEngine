#include "CircleRenderer.h"
#include <iostream>
#include <algorithm>
#include "Main/Game.h"
#include "Graphics/GLUtils.h"

CircleRenderer::CircleRenderer() {
    GLUtils::genQuad(_vaoCircle, _vboCircle, _ebo);
}

CircleRenderer::~CircleRenderer() {
}

void CircleRenderer::drawCircle(glm::vec2 center, const glm::vec3& color, float radius) {
    glm::vec4 vertices[4] = {
        // 左下角
        glm::vec4(center + glm::vec2(-radius, -radius) * 0.5f, 0, 1),
        // 右上角
        glm::vec4(center + glm::vec2(radius, radius) * 0.5f, 1, 0),
        // 左上角
        glm::vec4(center + glm::vec2(-radius, radius) * 0.5f, 0, 0),
        // 右下角
        glm::vec4(center + glm::vec2(radius, -radius) * 0.5f, 1, 1),
    };
    auto shader = Game::GetInstance().getGraphics()->getShaderManager()->getSpriteShader("circle");
    shader->setProjectionMatrix(Game::GetInstance().getProjectionMatrix());
    shader->setColor(color);
    shader->apply();
    glBindVertexArray(_vaoCircle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    // 替换顶点数据到当前Quad
    glBindBuffer(GL_ARRAY_BUFFER, _vboCircle);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 绘制Quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
