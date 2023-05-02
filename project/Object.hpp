#pragma once

#include <cstdlib>

#include "p6/p6.h"

#include "glimac/FreeflyCamera.hpp"
#include "ObjModel.hpp"
#include "ObjectProgram.hpp"
#include "Material.hpp"


using Vec = glm::vec3 ; 

class Object {

    private : 

        glm::mat4 MVMatrix;
        glm::mat4 ProjMatrix;

        void createVBO();

    protected : 
        Vec _position ; 

    public : 
        Object(const ObjModel& model, const ObjectProgram& program);
        ~Object();

        Vec get_position() const; 
        void draw(const FreeflyCamera &ViewMatrix, const int window_width, const int window_height); 


        const ObjModel& _model; 
        const ObjectProgram& _program; 
        GLuint _vbo;
}; 