#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/glm.hpp>
#include "Contents/Textures/Texture2D.h"

class SpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();

    void drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 pos, glm::vec2 size, glm::vec2 origin, float scale, float rotation, const glm::vec3& color);

private:
    GLuint _vao, _vbo, _ebo;
};
