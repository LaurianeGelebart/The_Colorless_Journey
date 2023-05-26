#pragma once

#include <cstdlib>
#include <map>

#include "p6/p6.h"

#include "programs/ColorProgram.hpp"
#include "FacesGroup.hpp"
#include "programs/ObjectProgram.hpp"
#include "programs/PanelProgram.hpp"
#include "programs/ShadowMapProgram.hpp"


class Object 
{

    private : 

    protected : 
        glm::vec3 _position ; 
        float _scale  = 0.1 ; 
        std::vector<FacesGroup> _model; 
        ObjectProgram* _program; 
        PanelProgram* _panelProgram; 
        // ShadowMapProgram& _shadowMapProgram;
        float _angleY = 0.f;
        int _lod = 0; 


    public : 
        Object(std::vector<FacesGroup> model, ObjectProgram& program);
        Object(std::vector<FacesGroup> model, PanelProgram& program);
        Object();
        // ~Object();
        
        void deleteVAO_VBO();

        glm::vec3 getPosition() const; 
        void draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color); 

    }; 