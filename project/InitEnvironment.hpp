#pragma once

#include <map>
#include <vector>
#include "Boid.hpp"
#include "Cloud.hpp"
#include "Content.hpp"
#include "IHM.hpp"
#include "Light.hpp"
#include "ModelPart.hpp"
#include "Object.hpp"
#include "Obstacle.hpp"
#include "PanelInfo.hpp"
#include "TrackballCamera.hpp"
#include "Wanderer.hpp"
#include "programs/ColorProgram.hpp"
#include "programs/ObjectProgram.hpp"
#include "programs/PanelProgram.hpp"

class InitEnvironment {
private:
    TrackballCamera _viewMatrix;

    IHM _ihm;

    std::vector<ModelPart> _firefly;
    std::vector<ModelPart> _puit;
    std::vector<ModelPart> _magic;
    std::vector<ModelPart> _content;
    std::vector<ModelPart> _fir1;
    std::vector<ModelPart> _fir2;
    std::vector<ModelPart> _fir3;
    std::vector<ModelPart> _mushroom1;
    std::vector<ModelPart> _mushroom2;
    std::vector<ModelPart> _house;
    std::vector<ModelPart> _rocks;
    std::vector<ModelPart> _rail;
    std::vector<ModelPart> _barel;
    std::vector<ModelPart> _cloud;
    std::vector<ModelPart> _panneau;
    std::vector<ModelPart> _sphere;
    std::vector<ModelPart> _panelColor;
    std::vector<ModelPart> _panelBeginning;
    std::vector<ModelPart> _panelOpen;
    std::vector<ModelPart> _sphereLOD;

    Obstacle randomObject(ObjectProgram& textureProgram);

public:
    InitEnvironment();

    void initObjectModel(std::map<std::string, Material>& materialMap);
    void initBoids(std::vector<Boid>& boids, ColorProgram& boidProgram, glm::vec3 magicPos);
    void initObstacles(std::vector<Obstacle>& obstacles, ObjectProgram& textureProgram, glm::vec3 magicPosition, glm::vec3 housePosition, glm::vec3 puitsPosition);
    void initClouds(std::vector<Cloud>& clouds, ObjectProgram& textureProgram);
    void initWanderer(Wanderer& firefly, ObjectProgram& textureProgram);
    void initContent(Content& box, ObjectProgram& textureProgram);
    void initPanels(std::vector<PanelInfo>& panelsInfo, PanelProgram& panelProgram, const TrackballCamera& viewMatrix);
    void initLighting(std::map<std::string, std::unique_ptr<Light>>& lightsMap, glm::vec3 magicPosition, glm::vec3 puitsPosition, glm::vec3 housePosition, glm::vec3 fireflyPosition);

    void addOrRemoveObstacles(std::vector<Obstacle>& obstacles, ObjectProgram& textureProgram);
    void addOrRemoveBoids(std::vector<Boid>& boids, ColorProgram& boidProgram, glm::vec3 magicPos);

    IHM& getIHM();
};
