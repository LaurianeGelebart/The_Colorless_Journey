#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "Object.hpp"
#include "PanelProgram.hpp"
#include "TrackballCamera.hpp"

class PanelInfo : public Object 
{ 
    private : 
        
        bool _isDisplay = false ;
        bool _hasBeenDislayed = false ;
        float _angleX = 0.0f; 

    public : 
        PanelInfo(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, PanelProgram& program);
        PanelInfo();

        void appears(const TrackballCamera& viewMatrix); 
        void disapears();

        bool getDisplay();
        bool getHasBeenDislayed();
        void draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color); 


}; 