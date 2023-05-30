#pragma once

#include "PanelInfo.hpp"
#include "p6/p6.h"

class InputManager {
private:
    bool _isMenu        = true;
    bool _colorPossible = false;

    bool _space         = false;
    bool _enter         = false;
    bool _alt           = false;
    bool _Z             = false;
    bool _S             = false;
    bool _Q             = false;
    bool _D             = false;
    bool _isMouseMoving = false;

    float _deltaY;
    float _deltaX;

public:
    InputManager();

    auto  getD() const -> bool;
    auto  getS() const -> bool;
    auto  getQ() const -> bool;
    auto  getZ() const -> bool;
    auto  getSpace() const -> bool;
    auto  getAlt() const -> bool;
    auto  getEnter() const -> bool;
    auto  getColorPossible() const -> bool;
    auto  getIsMouseMoving() const -> bool;
    auto getDeltaY() const -> float;
    auto getDeltaX() const -> float;

    void setIsMouseMovingToFalse();
    void setColorPossible(bool isOK);
    void blockControls();

    void InitMouseMove(p6::Context& ctx);
    void InitInput(p6::Context& ctx);
};
