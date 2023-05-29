#pragma once

#include "p6/p6.h"

struct ShadowMapProgram
{
    p6::Shader _Program;

    // GLint      uMVPMatrix;
    // GLint      uMVMatrix;
    // GLint      uNormalMatrix;

    // GLint uTexture;

    // GLint uKd;
    // GLint uKs;
    // GLint uShininess;

    // GLint uLightPos_vs;
    // GLint uLightDir_vs;
    // GLint uLightCharacter_vs;
    // GLint uLightIntensity;

    GLint uLightSpaceMatrix;
    GLint uDepthMap;
    GLint uModel;

    ShadowMapProgram() : _Program(p6::load_shader("./shaders/shadowMap.vs.glsl", "./shaders/shadowMap.fs.glsl"))
    {
        uDepthMap = glGetUniformLocation(_Program.id(), "udepthMap");
        uLightSpaceMatrix = glGetUniformLocation(_Program.id(), "uLightSpaceMatrix");
        uModel = glGetUniformLocation(_Program.id(), "uModel");
    
    }
};