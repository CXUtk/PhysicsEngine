#include "LineRenderer.h"
#include "Main/Game.h"
#include <algorithm>

LineRenderer::LineRenderer() {

    // 画线的顶点缓存
    glGenVertexArrays(1, &_vaoLine);
    glGenBuffers(1, &_vboLine);

    glBindVertexArray(_vaoLine);
    glBindBuffer(GL_ARRAY_BUFFER, _vboLine);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

LineRenderer::~LineRenderer() {
}

void LineRenderer::drawLines(const std::vector<glm::vec2>& lines, const glm::vec3& color, float width) {
    glLineWidth(width);

    auto defaultShader = Game::GetInstance().getShaderManager()->getSpriteShader("pure");
    defaultShader->setProjectionMatrix(Game::GetInstance().getProjectionMatrix());
    defaultShader->setColor(color);
    defaultShader->apply();

    int sz = lines.size();
    glBindVertexArray(_vaoLine);
    // 以1024个点为单位，分批绘制线段
    for (int i = 0; i < sz; i += BUFFER_SIZE) {
        glBindBuffer(GL_ARRAY_BUFFER, _vboLine);
        int count = std::min(sz, i + BUFFER_SIZE) - i;
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * count, lines.data() + i);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_LINES, 0, sz);
    }

    glBindVertexArray(0);
}
