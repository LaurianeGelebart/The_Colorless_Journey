#pragma once

#include "p6/p6.h"

struct ObjectProgram {
    p6::Shader _Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    GLint uTexture;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    GLint uLightMagic_vs;
    GLint uLightPuits_vs;
    GLint uLightHouse_vs;
    GLint uLightDir_vs;
    GLint uLightCharacter_vs;
    GLint uLightIntensity;

    ObjectProgram()
        : _Program(p6::load_shader("./shaders/3D.vs.glsl", "./shaders/texture.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(_Program.id(), "uNormalMatrix");

        uTexture = glGetUniformLocation(_Program.id(), "uTexture");

        uKd        = glGetUniformLocation(_Program.id(), "uKd");
        uKs        = glGetUniformLocation(_Program.id(), "uKs");
        uShininess = glGetUniformLocation(_Program.id(), "uShininess");

        uLightHouse_vs     = glGetUniformLocation(_Program.id(), "uLightHouse_vs");
        uLightPuits_vs     = glGetUniformLocation(_Program.id(), "uLightPuits_vs");
        uLightMagic_vs     = glGetUniformLocation(_Program.id(), "uLightMagic_vs");
        uLightDir_vs       = glGetUniformLocation(_Program.id(), "uLightDir_vs");
        uLightCharacter_vs = glGetUniformLocation(_Program.id(), "uLightCharacter_vs");
        uLightIntensity    = glGetUniformLocation(_Program.id(), "uLightIntensity");
    }
};