#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// 线渲染器
class LineRenderer {
public:
    LineRenderer();
    ~LineRenderer();

    void drawLines(const std::vector<glm::vec2>& lines, const glm::vec3& color, float width);

private:

    GLuint _vaoLine;
    GLuint _vboLine;

    static constexpr int BUFFER_SIZE = 1024;
};
