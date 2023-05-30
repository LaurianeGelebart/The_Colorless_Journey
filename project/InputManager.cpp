#include "InputManager.hpp"

InputManager::InputManager() {}

bool InputManager::getEnter()
{
    return this->_enter;
}
bool InputManager::getSpace()
{
    return this->_space;
}
bool InputManager::getAlt()
{
    return this->_alt;
}
bool InputManager::getZ()
{
    return this->_Z;
}
bool InputManager::getQ()
{
    return this->_Q;
}
bool InputManager::getS()
{
    return this->_S;
}
bool InputManager::getD()
{
    return this->_D;
}
bool InputManager::getIsMouseMoving()
{
    return this->_isMouseMoving;
}
float InputManager::getDeltaY()
{
    return this->_deltaY;
}
float InputManager::getDeltaX()
{
    return this->_deltaX;
}
void InputManager::setColorPossible(bool isOK)
{
    this->_colorPossible = isOK;
}
void InputManager::setIsMouseMovingToFalse()
{
    this->_isMouseMoving = false;
}
void InputManager::blockControls()
{
    this->_alt    = false;
    this->_enter  = false;
    this->_Z      = false;
    this->_Q      = false;
    this->_S      = false;
    this->_D      = false;
    this->_isMenu = true;
}

void InputManager::InitInput(p6::Context& ctx)
{
    ctx.key_pressed = [this](const p6::Key& key) {
        if (this->_isMenu)
        {
            if (key.physical == GLFW_KEY_ENTER || key.physical == GLFW_KEY_SPACE)
            {
                this->_enter  = true;
                this->_alt    = true;
                this->_isMenu = false;
            }
        }
        else
        {
            if (key.physical == GLFW_KEY_W)
                this->_Z = true;
            if (key.physical == GLFW_KEY_S)
                this->_S = true;
            if (key.physical == GLFW_KEY_A)
                this->_Q = true;
            if (key.physical == GLFW_KEY_D)
                this->_D = true;
            if (key.physical == GLFW_KEY_LEFT_ALT)
                this->_alt = !this->_alt;
            if (key.physical == GLFW_KEY_SPACE)
            {
                if (this->_colorPossible)
                    this->_space = !this->_space;
            }
        }
    };

    ctx.key_released = [this](const p6::Key& key) {
        if (!this->_isMenu)
        {
            if (key.physical == GLFW_KEY_W)
                this->_Z = false;
            if (key.physical == GLFW_KEY_S)
                this->_S = false;
            if (key.physical == GLFW_KEY_A)
                this->_Q = false;
            if (key.physical == GLFW_KEY_D)
                this->_D = false;
        }
    };
}

void InputManager::InitMouseMove(p6::Context& ctx)
{
    ctx.mouse_moved = [this](p6::MouseMove data) {
        if (this->_alt)
        {
            this->_deltaY        = data.delta.y;
            this->_deltaX        = data.delta.x;
            this->_isMouseMoving = true;
        }
    };
}
