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
#include "InputManager.hpp"
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
        InputManager _inputSystem; 

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


        std::vector<PanelInfo> _panelsInfo;
        std::vector<Boid> _boids;
        std::vector<Obstacle> _obstacles;
        std::vector<Cloud> _clouds;
        Content _box ;
        Wanderer _firefly;

        std::map<std::string, std::unique_ptr<Light>> _lightsMap;
        std::map<std::string, Material> _materialMap;

      
        void initFBO();
        
        void checkLOD();

        void renderBoids();
        void renderObjects(p6::Context &ctx);
        void renderPanels();

        void inputManagement();
        void panelManagement();
        void colorManagement();

    public : 
        GameEnvironment(int  windowWidth, int  windowHeight);

        void initScene(p6::Context &ctx);
        void render(p6::Context &ctx);
        void environmentManagement();
        void deleteScene();
}; 
