#include "InputControls.h"
#include "Main/Game.h"

InputControls::InputControls() :_mousePos(glm::vec2(0)), _mouseLeftPressing(false), _wasMouseLeftPressing(false) {

}

InputControls& InputControls::GetInstance() {
    static InputControls control;
    return control;
}

void InputControls::preUpdate(float dt) {
    auto& game = Game::GetInstance();
    auto _window = game.getWindow().get();
    double xpos, ypos;
    glfwGetCursorPos(_window, &xpos, &ypos);
    int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);
    int rightState = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT);

    _mouseLeftPressing = (state == GLFW_PRESS);
    _mouseRightPressing = (rightState == GLFW_PRESS);
    _mousePos = glm::vec2(xpos, -ypos + game.getHeight());

    for (int i = 32; i < 400; i++) {
        _keyState[i] = (glfwGetKey(_window, i) == GLFW_PRESS);
    }
}

void InputControls::postUpdate(float dt) {
    _wasMouseLeftPressing = _mouseLeftPressing;
    _wasMouseRightPressing = _mouseRightPressing;
    _keyStateOld = _keyState;
}
