#pragma once
#include <glm/glm.hpp>

class Graphics {
public:
    Graphics();
    ~Graphics();
    void drawLine(glm::vec2 start, glm::vec2 end, const glm::vec3& color, float width);

private:

};
