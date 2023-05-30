#include "InitEnvironment.hpp"
#include "Loader.cpp"
#include "p6/p6.h"

InitEnvironment::InitEnvironment()
{}

IHM& InitEnvironment::getIHM()
{
    return this->_ihm;
}

void InitEnvironment::initObjectModel(std::map<std::string, Material>& materialMap)
{
    this->_puit           = Loader("./assets/models/puit.obj", materialMap);
    this->_magic          = Loader("./assets/models/magique.obj", materialMap);
    this->_content        = Loader("./assets/models/content.obj", materialMap);
    this->_fir1           = Loader("./assets/models/fir1.obj", materialMap);
    this->_fir2           = Loader("./assets/models/fir2.obj", materialMap);
    this->_fir3           = Loader("./assets/models/fir3.obj", materialMap);
    this->_mushroom1      = Loader("./assets/models/mushroom1.obj", materialMap);
    this->_mushroom2      = Loader("./assets/models/mushroom2.obj", materialMap);
    this->_house          = Loader("./assets/models/house.obj", materialMap);
    this->_rocks          = Loader("./assets/models/rocks.obj", materialMap);
    this->_rail           = Loader("./assets/models/rail.obj", materialMap);
    this->_barel          = Loader("./assets/models/barel.obj", materialMap);
    this->_cloud          = Loader("./assets/models/cloud1.obj", materialMap);
    this->_panneau        = Loader("./assets/models/panneau.obj", materialMap);
    this->_panelColor     = Loader("./assets/models/panel_color.obj", materialMap);
    this->_panelBeginning = Loader("./assets/models/panel_beginning.obj", materialMap);
    this->_panelOpen      = Loader("./assets/models/panel_open.obj", materialMap);
    this->_sphere         = Loader("./assets/models/sphere.obj", materialMap);
    this->_firefly        = Loader("./assets/models/firefly.obj", materialMap);
    this->_sphereLOD      = Loader("./assets/models/sphere_lod.obj", materialMap);
}

void InitEnvironment::initBoids(std::vector<Boid>& boids, ColorProgram& boidProgram, glm::vec3 magicPosition)
{
    for (int i = 0; i < this->_ihm.getNbBoids(); i++)
    {
        Boid b(this->_sphere, this->_sphereLOD, boidProgram, magicPosition);
        boids.push_back(b);
    }
}

void InitEnvironment::initObstacles(std::vector<Obstacle>& obstacles, ObjectProgram& textureProgram, glm::vec3 magicPosition, glm::vec3 housePosition, glm::vec3 puitsPosition)
{
    obstacles.emplace_back(this->_house, textureProgram, housePosition);
    obstacles.emplace_back(this->_puit, textureProgram, puitsPosition);
    obstacles.emplace_back(this->_rail, textureProgram, glm::vec3(-1.8, 0.0, 1.8));
    obstacles.emplace_back(this->_rocks, textureProgram, glm::vec3(-1.2, 0.0, -1.6));
    obstacles.emplace_back(this->_rocks, textureProgram, glm::vec3(-1.2, 0.0, 1.0));
    obstacles.emplace_back(this->_barel, textureProgram, glm::vec3(-0.4, 0.0, 0.0));
    obstacles.emplace_back(this->_barel, textureProgram, glm::vec3(-0.6, 0.0, -0.7));
    obstacles.emplace_back(this->_magic, textureProgram, magicPosition);
    obstacles.emplace_back(this->_panneau, textureProgram, glm::vec3(0.3, 0.0, 0.3));

    for (size_t i = obstacles.size(); i < this->_ihm.getNbObstacles(); i++)
    {
        obstacles.push_back(randomObject(textureProgram));
    }
}

Obstacle InitEnvironment::randomObject(ObjectProgram& textureProgram)
{
    float j = p6::random::number();
    if (j < 0.25)
    {
        return Obstacle(this->_fir1, textureProgram);
    }
    if (j < 0.5)
    {
        return Obstacle(this->_fir2, textureProgram);
    }
    if (j < 0.75)
    {
        return Obstacle(this->_fir3, textureProgram);
    }
    if (j < 0.90)
    {
        return Obstacle(this->_mushroom1, textureProgram);
    }
    return Obstacle(this->_mushroom2, textureProgram);
   
}

void InitEnvironment::initClouds(std::vector<Cloud>& clouds, ObjectProgram& textureProgram)
{
    for (int i = 0; i < 5; i++)
    {
        Cloud c(this->_cloud, textureProgram);
        clouds.push_back(c);
    }
}

void InitEnvironment::initWanderer(Wanderer& firefly, ObjectProgram& textureProgram)
{
    firefly = Wanderer(this->_firefly, textureProgram);
}

void InitEnvironment::initContent(Content& box, ObjectProgram& textureProgram)
{
    box = Content(this->_content, textureProgram);
}

void InitEnvironment::initPanels(std::vector<PanelInfo>& panelsInfo, PanelProgram& panelProgram, const TrackballCamera& viewMatrix)
{
    panelsInfo.emplace_back(this->_panelOpen, panelProgram);
    panelsInfo.emplace_back(this->_panelBeginning, panelProgram);
    panelsInfo.emplace_back(this->_panelColor, panelProgram);
    panelsInfo[0].appears(viewMatrix);
}

void InitEnvironment::initLighting(std::map<std::string, std::unique_ptr<Light>>& lightsMap, glm::vec3 magicPosition, glm::vec3 puitsPosition, glm::vec3 housePosition, glm::vec3 fireflyPosition)
{
    lightsMap["lightDir"]       = std::make_unique<DirectionalLight>(glm::vec3(0.f, 1.f, 0.f));
    lightsMap["lightMagic"]     = std::make_unique<PointLight>(magicPosition);
    lightsMap["lightPuits"]     = std::make_unique<PointLight>(puitsPosition);
    lightsMap["lightHouse"]     = std::make_unique<PointLight>(housePosition);
    lightsMap["lightCharacter"] = std::make_unique<PointLight>(fireflyPosition);
}

void InitEnvironment::addOrRemoveBoids(std::vector<Boid>& boids, ColorProgram& boidProgram, glm::vec3 magicPosition)
{
    size_t nbBoids = boids.size();

    if (nbBoids < this->_ihm.getNbBoids())
    {
        for (int i = 0; i < this->_ihm.getNbBoids() - nbBoids; i++)
        {
            Boid b(this->_sphere, this->_sphereLOD, boidProgram, magicPosition);
            boids.push_back(b);
        }
    }
    else if (nbBoids > this->_ihm.getNbBoids())
    {
        for (int i = 0; i < nbBoids - this->_ihm.getNbBoids(); i++)
        {
            boids.pop_back();
        }
    }
}

void InitEnvironment::addOrRemoveObstacles(std::vector<Obstacle>& obstacles, ObjectProgram& textureProgram)
{
    size_t nbObstacles = obstacles.size();

    if (nbObstacles < this->_ihm.getNbObstacles())
    {
        for (int i = 0; i < this->_ihm.getNbObstacles(); i++)
        {
            obstacles.push_back(randomObject(textureProgram));
        }
    }
    else if (nbObstacles > this->_ihm.getNbObstacles())
    {
        for (int i = 0; i < nbObstacles - this->_ihm.getNbObstacles(); i++)
        {
            obstacles.pop_back();
        }
    }
}
