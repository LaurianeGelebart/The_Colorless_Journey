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
#include "Light.hpp"
#include "Loader.hpp"
#include "Obstacle.hpp"
#include "Object.hpp"
#include "PanelInfo.hpp"
#include "Shadow.hpp"
#include "Texture.hpp"

#include "programs/ColorProgram.hpp"
#include "programs/ObjectProgram.hpp"
#include "programs/PanelProgram.hpp"
#include "programs/ShadowMapProgram.hpp"


class GameEnvironment 
{
    private : 
        InitEnvironment _initSystem; 
        Shadow _shadowSystem; 

        ObjectProgram _textureProgram ; 
        PanelProgram _panelProgram ; 
        ColorProgram _boidProgram ; 

        TrackballCamera _ViewMatrix;

        GLuint _shadowMapFBO ; 
        GLuint _shadowMap ; 

        float _movementStrength = 0.01;
        float _rotationStrength = 100.0;

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
        bool _alt = false;
      
        void initFBO();

        void colorManagement();
        void mouseMoveManagement(p6::Context &ctx);
        void checkLOD();

        void renderBoids();
        void renderObjects(p6::Context &ctx);
        void renderPanels();

    public : 
        std::vector<PanelInfo> panelsInfo;
        std::vector<Boid> boids;
        std::vector<Obstacle> obstacles;
        std::vector<Cloud> clouds;
        Content box ;
        Wanderer gaspard;

        std::map<std::string, std::unique_ptr<Light>> _lightsMap;

        std::map<std::string, Material> materialMap;

        GameEnvironment(int  windowWidth, int  windowHeight);

        void initScene();
        void render(p6::Context &ctx);
        void cameraManagement(); 
        void inputManagement(p6::Context &ctx);
        void deleteScene();
        void panelManagement(p6::Context &ctx);
}; 
