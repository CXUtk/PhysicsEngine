#include "PointRenderer.h"
#include "Main/Game.h"
#include <algorithm>

PointRenderer::~PointRenderer() {
}

void PointRenderer::drawPoints(std::vector<glm::vec2> points, const glm::vec3& color, float radius) {
    glPointSize(radius);
    auto defaultShader = Game::GetInstance().getShaderManager()->getDefaultShader();
    defaultShader->setColor(color);
    defaultShader->apply();

    glBindVertexArray(_vaoPoints);

    int sz = points.size();

    // 以1024个点为单位，分批绘制线段
    for (int i = 0; i < sz; i += BUFFER_SIZE) {
        glBindBuffer(GL_ARRAY_BUFFER, _vboPoints);
        int count = std::min(sz, i + BUFFER_SIZE) - i;
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec2) * count, points.data() + i);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_POINTS, 0, sz);
    }

    glBindVertexArray(0);
}


PointRenderer::PointRenderer() {
    // 对于只画一条线的顶点缓存
    glGenVertexArrays(1, &_vaoPoints);
    glGenBuffers(1, &_vboPoints);

    glBindVertexArray(_vaoPoints);
    glBindBuffer(GL_ARRAY_BUFFER, _vboPoints);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
