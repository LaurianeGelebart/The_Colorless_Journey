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
#include "Loader.hpp"
#include "Obstacle.hpp"
#include "Object.hpp"
#include "ObjectProgram.hpp"
#include "PanelInfo.hpp"
#include "PanelProgram.hpp"
#include "Texture.hpp"

class GameEnvironment 
{
    private : 
        ObjectProgram _textureProgram ; 
        PanelProgram _panelProgram ; 

        TrackballCamera _ViewMatrix;
        IHM _ihm ;

        float _movementStrength = 0.1;
        float _rotationStrength = 100.0;

        int _windowWidth  ; 
        int _windowHeight ; 

        bool _color = false;  

        glm::vec3 _magicPos = glm::vec3(1.2, 0.0, -1.2); 

        bool _Z = false;
        bool _S = false;
        bool _Q = false;
        bool _D = false;
        bool _alt = true;

        std::vector<FacesGroup> _puit ;
        std::vector<FacesGroup> _magic ;
        std::vector<FacesGroup> _content;
        std::vector<FacesGroup> _fir1 ;
        std::vector<FacesGroup> _fir2;
        std::vector<FacesGroup> _fir3 ;
        std::vector<FacesGroup> _mushroom1;
        std::vector<FacesGroup> _mushroom2 ;
        std::vector<FacesGroup> _house ;
        std::vector<FacesGroup> _rocks ;
        std::vector<FacesGroup> _rail ;
        std::vector<FacesGroup> _barel ;
        std::vector<FacesGroup> _cloud ;
        std::vector<FacesGroup> _panneau;
        std::vector<FacesGroup> _sphere ;
        std::vector<FacesGroup> _panelColor;
        std::vector<FacesGroup> _panelBeginning ;


        void initObjectModel();
        void initBoids();
        void initObstacles();
        void initClouds();
        void initWanderer();
        void initContent();
        void initFBO();
        void initPanels();

        void colorManagement();
        void mouseMoveManagement(p6::Context &ctx);

	// unsigned int shadowMapFBO;
	// unsigned int shadowMap;


    public : 
        std::vector<PanelInfo> panelsInfo;
        std::vector<Boid> boids;
        std::vector<Obstacle> obstacles;
        std::vector<Cloud> clouds;
        std::map<std::string, Material> materialMap;
        Content box ;
        Wanderer gaspard;

        GameEnvironment(int  windowWidth, int  windowHeight);

        void initScene();
        void render(p6::Context &ctx);
        void cameraManagement(); 
        void inputManagement(p6::Context &ctx);
        void deleteScene();
        void addOrRemoveObstacles();
        void addOrRemoveBoids();

}; 
