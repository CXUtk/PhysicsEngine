#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();
    void drawText(glm::vec2 pos, const std::string& text, float scale, const glm::vec3& color);
    glm::ivec2 measureString(const std::string& font, const std::string& text, float scale) const;

private:
    GLuint _vao, _vbo, _ebo;
    void draw_quad(GLuint textureId, glm::vec2 bottomLeft, glm::vec2 size);
};
