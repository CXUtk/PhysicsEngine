#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Contents/Scenes/SceneManager.h"
#include "Contents/Fonts/FontManager.h"
#include "Graphics/Shaders/ShaderManager.h"
#include "Graphics/Graphics.h"


class Game {
public:
    static Game& GetInstance();
    ~Game();

    void run();

    std::shared_ptr<GLFWwindow> getWindow() { return _window; }
    std::shared_ptr<FontManager> getFontManager() { return _fontManager; }
    std::shared_ptr<SceneManager> getSceneManager() { return _sceneManager; }
    std::shared_ptr<ShaderManager> getShaderManager() { return _shaderManager; }
    std::shared_ptr<Graphics> getGraphics() { return _graphics; }


    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    glm::mat4 getProjectionMatrix() { return _projectionMatrix; }

private:
    // 构造函数private声明，确保单例
    Game(int width, int height);

    int _width, _height;

    double _fpsTimeOld;
    int _fpsCounter;

    std::shared_ptr<GLFWwindow> _window;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<FontManager> _fontManager;
    std::shared_ptr<ShaderManager> _shaderManager;
    std::shared_ptr<Graphics> _graphics;


    glm::mat4 _projectionMatrix;

    void update(float delta);
    void draw(float delta);
};
