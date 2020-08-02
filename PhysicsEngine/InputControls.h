#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <bitset>

class InputControls {
public:
    static InputControls& GetInstance();

    void preUpdate(float dt);
    void postUpdate(float dt);
    bool isLeftClicked() const { return !_wasMouseLeftPressing && _mouseLeftPressing; }
    bool isMouseLeftDown() const { return _mouseLeftPressing; }
    glm::vec2 getMousePos() const { return _mousePos; }
    bool isKeyJustPress(int keyCode) const { return _keyState[keyCode] && !_keyStateOld[keyCode]; }

private:
    InputControls();
    glm::vec2 _mousePos;
    bool _mouseLeftPressing;
    bool _wasMouseLeftPressing;

    std::bitset<500> _keyState;
    std::bitset<500> _keyStateOld;
};
