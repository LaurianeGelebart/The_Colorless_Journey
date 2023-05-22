#pragma once

#include <cstdlib>
#include <map>

#include "p6/p6.h"

#include "FacesGroup.hpp"
#include "ObjectProgram.hpp"
#include "PanelProgram.hpp"
#include "ShadowMapProgram.hpp"


class Object 
{

    private : 

    protected : 
        glm::vec3 _position ; 
        float _scale  = 0.1 ; 
        std::vector<std::vector<FacesGroup>> _models; 
        ObjectProgram* _program; 
        PanelProgram* _panelProgram; 
        // ShadowMapProgram& _shadowMapProgram;
        float _angleY = 0.f;
        int _lod = 0; 


    public : 
        Object(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program);
        Object(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, PanelProgram& program);
        Object();
        // ~Object();
        
        void checkLOD(glm::vec3 gaspardPosition);
        void deleteVAO_VBO();

        glm::vec3 getPosition() const; 
        void draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color); 

    }; 