#pragma once

#include "p6/p6.h"

struct ObjectProgram
{
    p6::Shader m_Program;

    GLint      uMVPMatrix;
    GLint      uMVMatrix;
    GLint      uNormalMatrix;

    GLint uTexture1;
    GLint uTexture2;

    GLint uKd;
    GLint uKs;
    GLint uShininess;

    //GLint uLightPos_vs;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    // ObstaclesProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/pointlight.fs.glsl"))
    ObjectProgram() : m_Program(p6::load_shader("shaders/3D.vs.glsl", "shaders/directionallight.fs.glsl"))
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        
        uTexture1 = glGetUniformLocation(m_Program.id(), "uTexture1");
        uTexture2 = glGetUniformLocation(m_Program.id(), "uTexture2");

        uKd        = glGetUniformLocation(m_Program.id(), "uKd");
        uKs        = glGetUniformLocation(m_Program.id(), "uKs");
        uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        //uLightPos_vs    = glGetUniformLocation(m_Program.id(), "uLightPos_vs");
        uLightDir_vs    = glGetUniformLocation(m_Program.id(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.id(), "uLightIntensity");
    }
};