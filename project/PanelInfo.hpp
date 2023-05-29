#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "programs/PanelProgram.hpp"
#include "FacesGroup.hpp"
#include "TrackballCamera.hpp"

class PanelInfo 
{ 
    private : 
        PanelProgram* _panelProgram; 
        std::vector<FacesGroup> _model; 
        glm::vec3 _position ; 
        float _angleX = 0.0f; 
        float _angleY = 0.f;
        float _scale  = 0.1 ; 
        
        bool _isDisplay = false ;
        bool _hasBeenDislayed = false ;

    public : 
        PanelInfo(std::vector<FacesGroup> model, PanelProgram& program);
        PanelInfo();

        void appears(const TrackballCamera& viewMatrix); 
        void disapears();

        bool getDisplay();
        bool getHasBeenDislayed();
        void draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color); 

        void deleteVAO_VBO();

}; 