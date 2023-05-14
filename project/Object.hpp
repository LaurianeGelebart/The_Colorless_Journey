#pragma once

#include <cstdlib>
#include <map>

#include "p6/p6.h"

#include "FreeflyCamera.hpp"
#include "FacesGroup.hpp"
#include "ObjectProgram.hpp"
#include "Material.hpp"


using Vec = glm::vec3 ; 

class Object {

    private : 


    protected : 
        Vec _position ; 
        float _scale  = 0.1 ; 
        std::vector<FacesGroup> _facesGroup; 
        ObjectProgram& _program; 

    public : 
        Object(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        // Object();
        // ~Object();
        
        void deleteVAO_VBO();

        Vec get_position() const; 
        void draw(const FreeflyCamera &ViewMatrix, const int window_width, const int window_height, std::map<std::string, Material>& materialMap); 

        // GLuint     brick_texture;
        // GLuint     wood_texture;
    }; 