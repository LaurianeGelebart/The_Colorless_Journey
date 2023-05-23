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


class GameEnvironment 
{
    private : 
        InitEnvironment _initGame; 

        ObjectProgram _textureProgram ; 
        PanelProgram _panelProgram ; 
        ColorProgram _boidProgram ; 
        ShadowMapProgram _shadowProgram ; 

        TrackballCamera _ViewMatrix;

        GLuint _shadowMapFBO ; 
        GLuint _shadowMap ; 

        float _movementStrength = 0.1;
        float _rotationStrength = 100.0;


	int shadowMapWidth = 2048, shadowMapHeight = 2048;

        int _windowWidth  ; 
        int _windowHeight ; 

        bool _color = false;  

        glm::vec3 _magicPosition = glm::vec3(1.2, 0.0, -1.2); 
        glm::vec3 _housePosition = glm::vec3(-1.1, 0.0, -0.0); 
        glm::vec3 _puitsPosition = glm::vec3(1.0, 0.0, 1.0); 

        bool _Z = false;
        bool _S = false;
        bool _Q = false;
        bool _D = false;
        bool _alt = true;
      
        void initFBO();

        void colorManagement();
        void mouseMoveManagement(p6::Context &ctx);


    public : 
        std::vector<PanelInfo> panelsInfo;
        std::vector<Boid> boids;
        std::vector<Obstacle> obstacles;
        std::vector<Cloud> clouds;
        Content box ;
        Wanderer gaspard;

        std::map<std::string, Material> materialMap;

        GameEnvironment(int  windowWidth, int  windowHeight);

        void initScene();
        void render(p6::Context &ctx);
        void cameraManagement(); 
        void inputManagement(p6::Context &ctx);
        void deleteScene();

}; 
