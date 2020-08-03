#include "LineRenderer.h"
#include "Main/Game.h"

LineRenderer::LineRenderer() {

    // 对于只画一条线的顶点缓存
    glGenVertexArrays(1, &_vaoLine);
    glGenBuffers(1, &_vboLine);

    glBindVertexArray(_vaoLine);
    glBindBuffer(GL_ARRAY_BUFFER, _vboLine);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 2, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

LineRenderer::~LineRenderer() {
}

void LineRenderer::drawLines(std::vector<glm::vec2> lines, const glm::vec3& color, float width) {
    glLineWidth(width);

    auto defaultShader = Game::GetInstance().getShaderManager()->getDefaultShader();
    defaultShader->setColor(color);
    defaultShader->apply();

    glBindVertexArray(_vaoLine);
    glBindBuffer(GL_ARRAY_BUFFER, _vboLine);

    int sz = lines.size();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * sz, lines.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_LINES, 0, sz);

    glBindVertexArray(0);
}

LineRenderer& LineRenderer::getInstance() {
    static LineRenderer renderer;
    return renderer;
}
