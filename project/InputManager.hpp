#pragma once

#include <cstdlib>

#include "p6/p6.h"

#include "PanelInfo.hpp"


class InputManager 
{
    private : 
        bool _isMenu = true;  
        bool _colorPossible = false;  
        
        bool _space = false;  
        bool _enter = false;  
        bool _alt = false;
        bool _Z = false;
        bool _S = false;
        bool _Q = false;
        bool _D = false;
        bool _isMouseMoving =false ; 

        float _deltaY; 
        float _deltaX; 

    public : 
        InputManager();

        bool getD(); 
        bool getS(); 
        bool getQ(); 
        bool getZ(); 
        bool getSpace(); 
        bool getAlt(); 
        bool getEnter();
        bool getColorPossible();
        bool getIsMouseMoving();
        float getDeltaY(); 
        float getDeltaX();  
        
        void setIsMouseMovingToFalse();
        void setColorPossible(bool isOK); 
        void blockControls();

        void InitMouseMove(p6::Context &ctx);
        void InitInput(p6::Context &ctx);
}; 
