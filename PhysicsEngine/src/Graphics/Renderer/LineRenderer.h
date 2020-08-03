#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// 线渲染器
class LineRenderer {
public:
    ~LineRenderer();

    void drawLines(std::vector<glm::vec2> lines, const glm::vec3& color, float width);
    static LineRenderer& getInstance();

private:
    LineRenderer();

    GLuint _vaoLine;
    GLuint _vboLine;
};
