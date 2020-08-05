#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// 线渲染器
class PointRenderer {
public:
    PointRenderer();
    ~PointRenderer();

    void drawPoints(std::vector<glm::vec2> points, const glm::vec3& color, float radius);

private:

    GLuint _vaoPoints;
    GLuint _vboPoints;

    static constexpr int BUFFER_SIZE = 1024;
};
