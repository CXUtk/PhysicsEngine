#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "SceneManager.h"
#include "FontManager.h"


class Game {
public:
    static Game& GetInstance();
    ~Game();

    void run();

    std::shared_ptr<GLFWwindow> getWindow() { return _window; }
    std::shared_ptr<FontManager> getFontManager() { return _fontManager; }
    std::shared_ptr<SceneManager> getSceneManager() { return _sceneManager; }


    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }

private:
    // 构造函数private声明，确保单例
    Game(int width, int height);

    int _width, _height;
    std::shared_ptr<GLFWwindow> _window;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<FontManager> _fontManager;
    double _fpsTimeOld;
    int _fpsCounter;

    void update(float delta);
    void draw(float delta);
};
