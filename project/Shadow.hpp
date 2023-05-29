#pragma once

#include <cstdlib>
#include <vector>
#include <map>

#include "p6/p6.h"

#include "Wanderer.hpp"
#include "Boid.hpp"
#include "Cloud.hpp"
#include "Content.hpp"
#include "FacesGroup.hpp"
#include "FreeflyCamera.hpp"
#include "TrackballCamera.hpp"
#include "IHM.hpp"
#include "InitEnvironment.hpp"
#include "Loader.hpp"
#include "Obstacle.hpp"
#include "Object.hpp"
#include "PanelInfo.hpp"
#include "Texture.hpp"

#include "programs/ColorProgram.hpp"
#include "programs/ObjectProgram.hpp"
#include "programs/PanelProgram.hpp"
#include "programs/ShadowMapProgram.hpp"


class Shadow 
{
    private : 
        ShadowMapProgram _shadowProgram ; 

        GLuint _shadowMapFBO ; 
        GLuint _shadowMap ; 

        int _shadowMapWidth = 2048; 
        int _shadowMapHeight = 2048;

        glm::mat4 _lightSpaceMatrix;
        glm::mat4 _MVMatrix;

       float _nearPlane = 1.0f, _farPlane = 7.5f;

        void drawShadow(Object& model);
        void updateMatrix(Object& model, const glm::vec3 ViewMatrix, const glm::vec3 VLightMatrix); 


    public : 
        Shadow(); 
        void initFBO();
        void renderShadow(Object& model, const glm::vec3 ViewMatrix, const glm::vec3 VLightMatrix);
       
}; 
