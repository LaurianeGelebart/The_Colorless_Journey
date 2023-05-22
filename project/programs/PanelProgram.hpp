#pragma once

#include "p6/p6.h"

struct PanelProgram
{
    p6::Shader _Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uTexture;

    PanelProgram() : _Program(p6::load_shader("./shaders/3D.vs.glsl", "./shaders/panel.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_Program.id(), "uNormalMatrix");
        
        uTexture = glGetUniformLocation(_Program.id(), "uTexture");

    }
};