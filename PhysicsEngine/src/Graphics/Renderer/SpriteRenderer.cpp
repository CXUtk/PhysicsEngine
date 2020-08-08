#include "SpriteRenderer.h"
#include "Graphics/GLUtils.h"
#include "Main/Game.h"

SpriteRenderer::SpriteRenderer() {
    GLUtils::genQuad(_vao, _vbo, _ebo);
}

SpriteRenderer::~SpriteRenderer() {
}

void SpriteRenderer::drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 pos, glm::vec2 size, glm::vec2 origin, float scale, float rotation, const glm::vec3& color) {
    auto shader = Game::GetInstance().getGraphics()->getShaderManager()->getSpriteShader("default");

    auto model = glm::identity<glm::mat4>();
    model = glm::translate(model, glm::vec3(pos, 0));

    model = glm::translate(model, glm::vec3(origin, 0));
    model = glm::rotate(model, rotation, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(size.x * scale, size.y * scale, 1));
    model = glm::translate(model, glm::vec3(-origin, 0));


    shader->setModelMatrix(model);
    shader->setProjectionMatrix(Game::GetInstance().getProjectionMatrix());
    shader->setColor(color);

    shader->apply();

    glm::vec4 vertices[4] = {
        // 左下角
        glm::vec4(0, 0, 0, 1),
        // 右上角
        glm::vec4(1, 1, 1, 0),
        // 左上角
        glm::vec4(0, 1, 0, 0),
        // 右下角
        glm::vec4(1, 0, 1, 1),
    };


    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);

    glBindTexture(GL_TEXTURE_2D, texture->getId());
    // 替换顶点数据到当前Quad
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // 绘制Quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}
