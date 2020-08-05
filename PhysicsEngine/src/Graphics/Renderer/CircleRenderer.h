#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// 线渲染器
class CircleRenderer {
public:
    CircleRenderer();
    ~CircleRenderer();

    void drawCircle(glm::vec2 center, const glm::vec3& color, float radius);

private:

    GLuint _vaoCircle;
    GLuint _vboCircle, _ebo;
};
