#include "InputControls.h"
#include "Game.h"

InputControls::InputControls() :_mousePos(glm::vec2(0)), _mouseLeftPressing(false), _wasMouseLeftPressing(false) {

}

InputControls& InputControls::GetInstance() {
    static InputControls control;
    return control;
}

void InputControls::preUpdate(float dt) {
    Game& game = Game::GetInstance();
    auto _window = game.getWindow().get();
    double xpos, ypos;
    glfwGetCursorPos(_window, &xpos, &ypos);
    int state = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT);

    _mouseLeftPressing = (state == GLFW_PRESS);
    _mousePos = glm::vec2(xpos, -ypos) - glm::vec2(game.getWidth(), -game.getHeight()) / 2.f;

    for (int i = 32; i < 400; i++) {
        _keyState[i] = (glfwGetKey(_window, i) == GLFW_PRESS);
    }
}

void InputControls::postUpdate(float dt) {
    _wasMouseLeftPressing = _mouseLeftPressing;
    _keyStateOld = _keyState;
}
