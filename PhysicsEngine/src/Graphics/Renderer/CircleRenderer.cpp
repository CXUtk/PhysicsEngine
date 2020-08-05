#include "CircleRenderer.h"
#include <iostream>
#include <algorithm>
#include "Main/Game.h"

CircleRenderer::CircleRenderer() {
    // 不会变的顶点列表
    unsigned int indices[] = {
        0, 1, 3,
        0, 2, 1,
    };

    // 准备绘制一个Quad需要的顶点缓存序列
    // 一个Quad由4个顶点和两个三角形组成
    glGenVertexArrays(1, &_vaoCircle);
    glGenBuffers(1, &_vboCircle);
    glGenBuffers(1, &_ebo);


    glBindVertexArray(_vaoCircle);

    // 绑定VAO到四个顶点
    glBindBuffer(GL_ARRAY_BUFFER, _vboCircle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 4, nullptr, GL_DYNAMIC_DRAW);

    // 绑定顶点序列到indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);

    // 解除当前绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    auto shader = Game::GetInstance().getShaderManager()->getCircleShader();
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
