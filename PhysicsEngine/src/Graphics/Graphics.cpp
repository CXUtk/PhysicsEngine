﻿#include "Graphics.h"
#include "Renderer/LineRenderer.h"
#include "Renderer/PointRenderer.h"

Graphics::Graphics() {
    _shaderManager = std::make_shared<ShaderManager>();

    _lineRenderer = std::make_unique<LineRenderer>();
    _textRenderer = std::make_unique<TextRenderer>();
    _pointRenderer = std::make_unique<PointRenderer>();
    _circleRenderer = std::make_unique<CircleRenderer>();
    _spriteRenderer = std::make_unique<SpriteRenderer>();
}

Graphics::~Graphics() {
}

void Graphics::drawLine(glm::vec2 start, glm::vec2 end, const glm::vec3& color, float width) {
    _lineRenderer->drawLines({ start, end }, color, width);
}

void Graphics::drawLines(const std::vector<glm::vec2>& lines, const glm::vec3& color, float width) {
    _lineRenderer->drawLines(lines, color, width);
}

void Graphics::drawPoints(const std::vector<glm::vec2>& points, const glm::vec3& color, float radius) {
    _pointRenderer->drawPoints(points, color, radius);
}

void Graphics::drawText(glm::vec2 pos, const std::string& text, float scale, const glm::vec3& color) {
    _textRenderer->drawText(pos, text, scale, color);
}

void Graphics::drawCircle(glm::vec2 center, float radius, const glm::vec3& color) {
    _circleRenderer->drawCircle(center, color, radius);
}

void Graphics::drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 pos, float scale, const glm::vec3& color) {
    glm::vec2 origin = glm::vec2(0.5f, 0.5f);
    _spriteRenderer->drawSprite(texture, pos, texture->getSize(), origin, scale, 0, color);
}

void Graphics::drawSprite(std::shared_ptr<Texture2D> texture, glm::vec2 pos, glm::vec2 origin, float scale, float rotation, const glm::vec3& color) {
    _spriteRenderer->drawSprite(texture, pos, texture->getSize(), origin, scale, rotation, color);
}

glm::ivec2 Graphics::measureString(const std::string& font, const std::string& text, float scale) const {
    return _textRenderer->measureString(font, text, scale);
}
