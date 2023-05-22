#pragma once

#include "p6/p6.h"

struct ColorProgram
{
    p6::Shader _Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    GLint uLightPos_vs;
    GLint uLightIntensity;

    ColorProgram() : _Program(p6::load_shader("./shaders/3D.vs.glsl", "./shaders/color.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_Program.id(), "uNormalMatrix");
        
        uKd        = glGetUniformLocation(_Program.id(), "uKd");
        uKs        = glGetUniformLocation(_Program.id(), "uKs");
        uShininess = glGetUniformLocation(_Program.id(), "uShininess");

        uLightPos_vs    = glGetUniformLocation(_Program.id(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(_Program.id(), "uLightIntensity");
    }
};