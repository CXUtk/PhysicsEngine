#include "ShaderManager.h"

static std::string defaultVertPath = "Resources/Shaders/graphic.vert";
static std::string pure2DVertPath = "Resources/Shaders/graphic2.vert";

static std::string defaultFragPath = "Resources/Shaders/graphic.frag";
static std::string fontFragPath = "Resources/Shaders/font.frag";
static std::string circleFragPath = "Resources/Shaders/circle.frag";
static std::string pureFragPath = "Resources/Shaders/pure.frag";

ShaderManager::ShaderManager() {
    auto defaultShader = std::make_shared<SpriteShaderData>(ShaderData::loadShaderProgram(defaultVertPath, defaultFragPath));
    _spriteShaders["default"] = defaultShader;

    auto fontShader = std::make_shared<SpriteShaderData>(ShaderData::loadShaderProgram(defaultVertPath, fontFragPath));
    _spriteShaders["font"] = fontShader;

    auto circleShader = std::make_shared<SpriteShaderData>(ShaderData::loadShaderProgram(defaultVertPath, circleFragPath));
    _spriteShaders["circle"] = circleShader;

    auto pureShader = std::make_shared<SpriteShaderData>(ShaderData::loadShaderProgram(pure2DVertPath, pureFragPath));
    _spriteShaders["pure"] = pureShader;
}

ShaderManager::~ShaderManager() {
}

void ShaderManager::update(float delta) {
}
