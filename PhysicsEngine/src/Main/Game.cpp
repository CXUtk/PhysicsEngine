#include "Game.h"

#include <iostream>
#include <algorithm>
#include <glm/gtx/transform.hpp>

#include "Graphics/Renderer/TextRenderer.h"
#include "Controls/InputControls.h"


static int currentFPS;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Game& game = Game::GetInstance();
    game.setWidth(width);
    game.setHeight(height);
}

Game::Game(int width, int height) :_width(width), _height(height) {
    _fpsTimeOld = 0;
    _fpsCounter = 0;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, "Physics", nullptr, nullptr),
        [](GLFWwindow* ptr)->void {
            glfwDestroyWindow(ptr);
        });
    if (!_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_window.get());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load glad!" << std::endl;
        glfwTerminate();
        return;
    }
    glfwSetFramebufferSizeCallback(_window.get(), framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);


    _graphics = std::make_shared<Graphics>();
    _sceneManager = std::make_shared<SceneManager>();
    _fontManager = std::make_shared<FontManager>();
    _textureManager = std::make_shared<TextureManager>();

    _projectionMatrix = glm::ortho(0.f, static_cast<float>(_width), 0.f, static_cast<float>(_height));

}

Game::~Game() {
    glfwTerminate();
}

void Game::run() {
    _fpsTimeOld = glfwGetTime();
    double curTime = glfwGetTime();
    double elapsedTime = 0.016;
    while (!glfwWindowShouldClose(_window.get())) {
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        elapsedTime = std::min(elapsedTime, 0.016);
        update(elapsedTime);
        draw(elapsedTime);


        glfwSwapBuffers(_window.get());
        glfwPollEvents();


        double timeNow = glfwGetTime();
        elapsedTime = timeNow - curTime;

        // FPS 计算
        _fpsCounter++;
        if (timeNow - _fpsTimeOld > 1.0) {
            _fpsTimeOld = glfwGetTime();
            currentFPS = _fpsCounter;
            std::cout << "FPS:" << _fpsCounter << std::endl;
            _fpsCounter = 0;
        }
        curTime = timeNow;
    }
}

Game& Game::GetInstance() {
    static Game game(800, 600);
    return game;
}

void Game::update(float delta) {
    _projectionMatrix = glm::ortho(0.f, static_cast<float>(_width), 0.f, static_cast<float>(_height));
    InputControls::GetInstance().preUpdate(delta);
    _sceneManager->update(delta);
    InputControls::GetInstance().postUpdate(delta);
}

void Game::draw(float delta) {
    _sceneManager->draw(delta);
    auto fpsText = std::to_string(currentFPS);
    auto size = getGraphics()->measureString("default", fpsText, 1);


    getGraphics()->drawText(glm::vec2(0, _height - size.y), fpsText, 1, glm::vec3(1, 0, 0));
    auto texture = getTextureManager()->getTexture("icon");
    getGraphics()->drawSprite(texture, glm::vec2(200, 200), 1, glm::vec3(1, 1, 1));
}
