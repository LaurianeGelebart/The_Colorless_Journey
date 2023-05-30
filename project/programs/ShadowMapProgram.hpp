#pragma once

#include "p6/p6.h"

struct ShadowMapProgram {
    p6::Shader _Program;

    GLint uLightSpaceMatrix;
    GLint uDepthMap;
    GLint uModel;

    ShadowMapProgram()
        : _Program(p6::load_shader("./shaders/shadowMap.vs.glsl", "./shaders/shadowMap.fs.glsl"))
    {
        uDepthMap         = glGetUniformLocation(_Program.id(), "udepthMap");
        uLightSpaceMatrix = glGetUniformLocation(_Program.id(), "uLightSpaceMatrix");
        uModel            = glGetUniformLocation(_Program.id(), "uModel");
    }
};