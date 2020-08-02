#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>


class Scene {
public:
    static std::shared_ptr<Scene> makeScene(const std::string& name);

    Scene() = default;
    virtual void update(float delta) = 0;
    virtual void draw(float delta) = 0;
    virtual ~Scene() = 0;
};
