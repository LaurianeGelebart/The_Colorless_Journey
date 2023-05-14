#pragma once

#include <cstdlib>
#include <vector>
#include <map>

#include "p6/p6.h"

#include "Arpenteur.hpp"
#include "Boid.hpp"
#include "Cloud.hpp"
#include "Content.hpp"
#include "FacesGroup.hpp"
#include "FreeflyCamera.hpp"
#include "IHM.hpp"
#include "Loader.hpp"
#include "Obstacle.hpp"
#include "Object.hpp"
#include "ObjectProgram.hpp"
#include "Texture.hpp"

class GameEnvironment 
{
    private : 
        ObjectProgram _textureProgram ; 
        // ObjectProgram _puitProgram ; 

        FreeflyCamera _ViewMatrix;
    float                 movementStrength = 100.f;
    float                 rotationStrength = 1000.f;
    
        IHM _ihm ;
        int nb_slot = 0;

        int window_width = 1920 ; 
        int window_height = 1080 ; 


    bool _Z = false;
    bool _S = false;
    bool _Q = false;
    bool _D = false;

        std::vector<FacesGroup> _puit ;
        std::vector<FacesGroup> _magic ;
        std::vector<FacesGroup> _content;
        std::vector<FacesGroup> _fir1 ;
        std::vector<FacesGroup> _fir2;
        std::vector<FacesGroup> _fir3 ;
        std::vector<FacesGroup> _mushroom1;
        std::vector<FacesGroup> _mushroom2 ;
        std::vector<FacesGroup> _rock1 ;
        std::vector<FacesGroup> _rock2 ;
        std::vector<FacesGroup> _rock3;
        std::vector<FacesGroup> _house ;
        std::vector<FacesGroup> _rocks ;
        std::vector<FacesGroup> _rail ;
        std::vector<FacesGroup> _barel ;
        std::vector<FacesGroup> _cloud ;
        std::vector<FacesGroup> _panneau;
        std::vector<FacesGroup> _sphere ;


        Vec _magicPos = Vec(12.0, 0.0, -12.0); 

        void initObjectModel();
        void initBoids();
        void initObstacles();
        void initClouds();
        void initArpenteur();
        void initContent();

        void add_or_remove_obstacles();
        void add_or_remove_boids();


    public : 
        std::vector<Boid> boids;
        std::vector<Obstacle> obstacles;
        std::vector<Cloud> clouds;
        std::map<std::string, Material> materialMap;
        std::vector<Content> box ;
        std::vector<Arpenteur> gaspard;

        void initScene();
        void render(p6::Context &ctx);
        void cameraManagement(p6::Context &ctx);
        void deleteScene();

}; 
