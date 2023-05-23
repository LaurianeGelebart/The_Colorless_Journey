#include "p6/p6.h"

#include "InitEnvironment.hpp"

#include "glm/gtc/type_ptr.hpp"

InitEnvironment::InitEnvironment()
{}


void InitEnvironment::initObjectModel(std::map<std::string, Material>& materialMap)
{
    this->_puit = Loader("./assets/models/puit.obj", materialMap);
    this->_magic = Loader("./assets/models/magique.obj", materialMap);
    this->_content = Loader("./assets/models/content.obj", materialMap);
    this->_fir1 = Loader("./assets/models/fir1.obj", materialMap);
    this->_fir2 = Loader("./assets/models/fir2.obj", materialMap);
    this->_fir3 = Loader("./assets/models/fir3.obj", materialMap);
    this->_mushroom1 = Loader("./assets/models/mushroom1.obj", materialMap);
    this->_mushroom2 = Loader("./assets/models/mushroom2.obj", materialMap);
    this->_house = Loader("./assets/models/house.obj", materialMap);
    this->_rocks = Loader("./assets/models/rocks.obj", materialMap);
    this->_rail = Loader("./assets/models/rail.obj", materialMap);
    this->_barel = Loader("./assets/models/barel.obj", materialMap);
    this->_cloud = Loader("./assets/models/cloud1.obj", materialMap);
    this->_panneau = Loader("./assets/models/panneau.obj", materialMap);
    this->_panelColor = Loader("./assets/models/panel_color.obj", materialMap);
    this->_panelBeginning = Loader("./assets/models/panel_beginning.obj", materialMap);
    this->_sphere = Loader("./assets/models/sphere.obj", materialMap);
}

void InitEnvironment::initBoids(std::vector<Boid>& boids,  ColorProgram& boidProgram,  glm::vec3 magicPosition)
{
    for(int i=0 ; i<this->_ihm.getNbBoids() ; i++){
         Boid b(this->_sphere, this->_sphere, boidProgram, magicPosition) ;
         boids.push_back(b);
    }
}

void InitEnvironment::initObstacles(std::vector<Obstacle>& obstacles,  ObjectProgram& textureProgram,  glm::vec3 magicPosition, glm::vec3 housePosition, glm::vec3 puitsPosition)
{
    obstacles.push_back(Obstacle(this->_house, this->_house, textureProgram, housePosition)) ;
    obstacles.push_back(Obstacle(this->_puit, this->_puit, textureProgram, puitsPosition)) ;
    obstacles.push_back(Obstacle(this->_rail, this->_rail, textureProgram, glm::vec3(-1.8, 0.0, 1.8))) ;
    obstacles.push_back(Obstacle(this->_rocks, this->_rocks, textureProgram, glm::vec3(-1.2, 0.0, -1.6))) ;
    obstacles.push_back(Obstacle(this->_rocks, this->_rocks, textureProgram, glm::vec3(-1.2, 0.0, 1.0))) ;
    obstacles.push_back(Obstacle(this->_barel, this->_barel, textureProgram, glm::vec3(-0.4, 0.0, 0.0))) ;
    obstacles.push_back(Obstacle(this->_barel, this->_barel, textureProgram, glm::vec3(-0.6, 0.0, -0.7))) ;
    obstacles.push_back(Obstacle(this->_magic, this->_magic, textureProgram, magicPosition)) ;
    obstacles.push_back(Obstacle(this->_panneau, this->_panneau, textureProgram, glm::vec3(0.3, 0.0, 0.3))) ;

    for(int i=obstacles.size(); i < this->_ihm.getNbObstacles(); i++){
        float j = p6::random::number(); 
        if(j < 0.25) {
            obstacles.push_back(Obstacle(this->_fir1, this->_fir1, textureProgram));
        } else if(j < 0.5) {
            obstacles.push_back(Obstacle(this->_fir2, this->_fir2, textureProgram));
        } else if (j < 0.75){
            obstacles.push_back(Obstacle(this->_fir3, this->_fir3, textureProgram));
        } else if(j < 0.90) {
            obstacles.push_back(Obstacle(this->_mushroom1, this->_sphere, textureProgram));
        } else {
            obstacles.push_back(Obstacle(this->_mushroom2, this->_sphere, textureProgram));
        }
    }

  }

void InitEnvironment::initClouds(std::vector<Cloud>& clouds, ObjectProgram& textureProgram)
{
    for(int i=0 ; i<5 ; i++){
         Cloud c(this->_cloud, this->_cloud, textureProgram) ;
         clouds.push_back(c);
     }    
}

void InitEnvironment::initWanderer(Wanderer& gaspard, ObjectProgram& textureProgram)
{
    gaspard = Wanderer(this->_magic, this->_magic, textureProgram);
}

void InitEnvironment::initContent(Content& box, ObjectProgram& textureProgram)
{
    box = Content(this->_content, this->_content, textureProgram) ;
}

void InitEnvironment::initPanels(std::vector<PanelInfo>& panelsInfo, PanelProgram& panelProgram, const TrackballCamera& viewMatrix)
{
    panelsInfo.push_back(PanelInfo(this->_panelBeginning, this->_panelBeginning, panelProgram));
    panelsInfo.push_back(PanelInfo(this->_panelColor, this->_panelColor, panelProgram));
    panelsInfo[0].appears(viewMatrix);
}

void InitEnvironment::addOrRemoveBoids(std::vector<Boid>& boids,  ColorProgram& boidProgram,  glm::vec3 magicPosition)
{
    int nbBoids = boids.size();

    if (nbBoids < this->_ihm.getNbBoids()){
        for(int i=0 ; i< this->_ihm.getNbBoids()-nbBoids ; i++){
            Boid b(this->_sphere, this->_sphere, boidProgram, magicPosition) ;
            boids.push_back(b);
        }
    }
    else if (nbBoids > this->_ihm.getNbBoids()){
        for(int i=0 ; i< nbBoids-this->_ihm.getNbBoids() ; i++){
            boids.pop_back();
        }
    }
}

void InitEnvironment::addOrRemoveObstacles(std::vector<Obstacle>& obstacles,  ObjectProgram& textureProgram)
{
    int nbObstacles = obstacles.size();

    if (nbObstacles < this->_ihm.getNbObstacles()){
        for(int i=0 ; i< this->_ihm.getNbObstacles() ; i++){
            Obstacle o(this->_fir1, this->_fir1, textureProgram) ;
            obstacles.push_back(o);
        }
    }
    else if (nbObstacles > this->_ihm.getNbObstacles()){
        for(int i=0 ; i< nbObstacles-this->_ihm.getNbObstacles() ; i++){
            obstacles.pop_back();
        }
    }
}
