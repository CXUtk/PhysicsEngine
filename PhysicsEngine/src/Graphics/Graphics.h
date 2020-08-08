#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include "Graphics/Renderer/TextRenderer.h"
#include "Graphics/Renderer/LineRenderer.h"
#include "Graphics/Renderer/PointRenderer.h"
#include "Graphics/Renderer/CircleRenderer.h"
#include "Graphics/Renderer/SpriteRenderer.h"
#include "Contents/Textures/Texture2D.h"
#include "Graphics/Shaders/ShaderManager.h"

class Graphics {
public:
    Graphics();
    ~Graphics();

    void drawLine(glm::vec2 start, glm::vec2 end, const glm::vec3& color, float width);
    void drawLines(const std::vector<glm::vec2>& lines, const glm::vec3& color, float width);
    void drawPoints(const std::vector<glm::vec2>& points, const glm::vec3& color, float radius);
    void drawText(glm::vec2 pos, const std::string& text, float scale, const glm::vec3& color);
    void drawCircle(glm::vec2 center, float radius, const glm::vec3& color);
    void drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 pos, float scale, const glm::vec3& color);
    void drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 pos, glm::vec2 origin, float scale, float rotation, const glm::vec3& color);


    std::shared_ptr<ShaderManager> getShaderManager() const { return _shaderManager; }

    glm::ivec2 measureString(const std::string& font, const std::string& text, float scale) const;

private:
    std::unique_ptr<TextRenderer> _textRenderer;
    std::unique_ptr<LineRenderer> _lineRenderer;
    std::unique_ptr<PointRenderer> _pointRenderer;
    std::unique_ptr<CircleRenderer> _circleRenderer;
    std::unique_ptr<SpriteRenderer> _spriteRenderer;

    std::shared_ptr<ShaderManager> _shaderManager;
};
