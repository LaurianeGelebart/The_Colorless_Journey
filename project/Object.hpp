#pragma once

#include <cstdlib>
#include <map>

#include "p6/p6.h"

#include "TrackballCamera.hpp"
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
        float _angle = 0.f;

    public : 
        Object(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        // Object();
        // ~Object();
        
        void deleteVAO_VBO();

        Vec getPosition() const; 
        void draw(const TrackballCamera &ViewMatrix, const int window_width, const int window_height, std::map<std::string, Material>& materialMap, Vec ArpenteurPos, int color); 

        // GLuint     brick_texture;
        // GLuint     wood_texture;
    }; 