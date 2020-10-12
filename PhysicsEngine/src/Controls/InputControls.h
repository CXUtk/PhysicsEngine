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
    bool isMouseLeftUp() const { return _wasMouseLeftPressing && !_mouseLeftPressing; }
    bool isRightClicked()const { return !_wasMouseRightPressing && _mouseRightPressing; }
    bool isMouseRightDown() { return _mouseRightPressing; }
    bool isMouseRightUp() const { return _wasMouseRightPressing && !_mouseRightPressing; }
    glm::vec2 getMousePos() const { return _mousePos; }
    bool isKeyJustPress(int keyCode) const { return _keyState[keyCode] && !_keyStateOld[keyCode]; }

private:
    InputControls();
    glm::vec2 _mousePos;
    bool _mouseLeftPressing;
    bool _mouseRightPressing;
    bool _wasMouseLeftPressing;
    bool _wasMouseRightPressing;

    std::bitset<500> _keyState;
    std::bitset<500> _keyStateOld;
};
