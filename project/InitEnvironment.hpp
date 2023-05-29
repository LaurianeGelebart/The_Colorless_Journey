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
#include "IHM.hpp"
#include "Light.hpp"
#include "Loader.hpp"
#include "Obstacle.hpp"
#include "Object.hpp"
#include "PanelInfo.hpp"
#include "Texture.hpp"
#include "TrackballCamera.hpp"

#include "programs/ColorProgram.hpp"
#include "programs/ObjectProgram.hpp"
#include "programs/PanelProgram.hpp"
#include "programs/ShadowMapProgram.hpp"


class InitEnvironment  
{
    private :  

        TrackballCamera _ViewMatrix;

        std::vector<FacesGroup> _firefly ;
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
        std::vector<FacesGroup> _panelOpen ;
        std::vector<FacesGroup> _sphereLOD ;

    public : 
        InitEnvironment();

        void initObjectModel(std::map<std::string, Material>& materialMap);
        void initBoids(std::vector<Boid>& boids, ColorProgram& boidProgram, glm::vec3 magicPos);
        void initObstacles(std::vector<Obstacle>& obstacles, ObjectProgram& textureProgram, glm::vec3 magicPosition, glm::vec3 housePosition, glm::vec3 puitsPosition);
        void initClouds(std::vector<Cloud>& clouds, ObjectProgram& textureProgram);
        void initWanderer(Wanderer& gaspard, ObjectProgram& textureProgram);
        void initContent(Content& box, ObjectProgram& textureProgram);
        void initPanels(std::vector<PanelInfo>& panelsInfo, PanelProgram& panelProgram, const TrackballCamera& viewMatrix);
        void initLighting(std::map<std::string,std::unique_ptr<Light>>& lightsMap, glm::vec3 magicPosition, glm::vec3 puitsPosition, glm::vec3 housePosition, glm::vec3 gaspardPosition);

        void addOrRemoveObstacles(std::vector<Obstacle>& obstacles, ObjectProgram& textureProgram);
        void addOrRemoveBoids(std::vector<Boid>& boids, ColorProgram& boidProgram, glm::vec3 magicPos);

        IHM _ihm ;
}; 
