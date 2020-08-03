#include "Graphics.h"
#include "Renderer/LineRenderer.h"

Graphics::Graphics() {
}

Graphics::~Graphics() {
}

void Graphics::drawLine(glm::vec2 start, glm::vec2 end, const glm::vec3& color, float width) {
    LineRenderer::getInstance().drawLines({ start, end }, color, width);
}
