#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Graphics/Renderer/TextRenderer.h"
#include "Graphics/Renderer/LineRenderer.h"
#include "Graphics/Renderer/PointRenderer.h"
#include "Graphics/Renderer/CircleRenderer.h"

class Graphics {
public:
    Graphics();
    ~Graphics();

    void drawLine(glm::vec2 start, glm::vec2 end, const glm::vec3& color, float width);
    void drawLines(const std::vector<glm::vec2>& lines, const glm::vec3& color, float width);
    void drawPoints(const std::vector<glm::vec2>& points, const glm::vec3& color, float radius);
    void drawText(glm::vec2 pos, const std::string& text, float scale, const glm::vec3& color);
    void drawCircle(glm::vec2 center, float radius, const glm::vec3& color);


    glm::ivec2 measureString(const std::string& font, const std::string& text, float scale) const;

private:
    std::unique_ptr<TextRenderer> _textRenderer;
    std::unique_ptr<LineRenderer> _lineRenderer;
    std::unique_ptr<PointRenderer> _pointRenderer;
    std::unique_ptr<CircleRenderer> _circleRenderer;
};
