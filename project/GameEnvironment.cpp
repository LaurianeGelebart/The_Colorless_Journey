#include "GameEnvironment.hpp"
#include "IHM.hpp"
#include "glm/gtc/type_ptr.hpp"

GameEnvironment::GameEnvironment(int windowWidth, int windowHeight)
    : _windowWidth(windowWidth), _windowHeight(windowHeight)
{
}

void GameEnvironment::initScene(p6::Context& ctx)
{
    this->_initSystem.initObjectModel(this->_materialMap);
    this->_initSystem.initBoids(this->_boids, this->_boidProgram, this->_magicPosition);
    this->_initSystem.initObstacles(this->_obstacles, this->_textureProgram, this->_magicPosition, this->_housePosition, this->_puitsPosition);
    this->_initSystem.initClouds(this->_clouds, this->_textureProgram);
    this->_initSystem.initWanderer(this->_firefly, this->_textureProgram);
    this->_initSystem.initContent(this->_box, this->_textureProgram);
    this->_initSystem.initPanels(this->_panelsInfo, this->_panelProgram, this->_viewMatrix);
    this->_initSystem.initLighting(this->_lightsMap, this->_magicPosition, this->_puitsPosition, this->_housePosition, this->_firefly.getPosition());

    // this->_shadowSystem.initFBO();

    this->_inputSystem.InitInput(ctx);
    this->_inputSystem.InitMouseMove(ctx);
}

void GameEnvironment::deleteScene()
{
    for (auto& obstacle : this->_obstacles)
    {
        obstacle.deleteVAO_VBO();
    }
    for (auto& boid : this->_boids)
    {
        boid.deleteVAO_VBO();
    }
    for (auto& cloud : this->_clouds)
    {
        cloud.deleteVAO_VBO();
    }
    this->_firefly.deleteVAO_VBO();
    this->_box.deleteVAO_VBO();
    glfwTerminate();
}

void GameEnvironment::render(p6::Context& ctx)
{
    this->_initSystem.addOrRemoveBoids(this->_boids, this->_boidProgram, this->_magicPosition);
    this->_initSystem.addOrRemoveObstacles(this->_obstacles, this->_textureProgram);

    this->_initSystem.getIHM().draw();

    renderLights();
    // renderShadows();
    renderBoids();
    renderObjects(ctx);
    renderPanels();
}

void GameEnvironment::environmentManagement()
{
    panelManagement();
    colorManagement();
    inputManagement();
}

void GameEnvironment::renderLights()
{
    this->_lightsMap["lightCharacter"]->setPosition(this->_firefly.getPosition());
    for (auto& light : this->_lightsMap)
    {
        light.second->update(this->_viewMatrix.getViewMatrix());
    }
}

void GameEnvironment::renderShadows()
{
    // for(auto& obstacle : this->_obstacles){
    //     this->_shadowSystem.renderShadow(obstacle, this->_viewMatrix.getPosition(), this->_lightsMap["lightDir"]->getPosition());
    // }
}

void GameEnvironment::renderBoids()
{
    this->_boidProgram._Program.use();

    glUniform3fv(this->_boidProgram.uLightMagic_vs, 1, glm::value_ptr(this->_lightsMap["lightMagic"]->getPosition()));
    glUniform3fv(this->_boidProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.1)));

    for (auto& boid : this->_boids)
    {
        boid.checkLOD(this->_firefly.getPosition());
        boid.draw(this->_viewMatrix.getViewMatrix(), this->_windowWidth, this->_windowHeight, this->_materialMap);
        boid.collision(this->_boids, this->_obstacles, this->_initSystem.getIHM());
        boid.updatePosition();
    };
}

void GameEnvironment::renderObjects(p6::Context& ctx)
{
    this->_textureProgram._Program.use();

    glUniform3fv(this->_textureProgram.uLightDir_vs, 1, glm::value_ptr(this->_lightsMap["lightDir"]->getPosition()));
    glUniform3fv(this->_textureProgram.uLightMagic_vs, 1, glm::value_ptr(this->_lightsMap["lightMagic"]->getPosition()));
    glUniform3fv(this->_textureProgram.uLightCharacter_vs, 1, glm::value_ptr(this->_lightsMap["lightCharacter"]->getPosition()));
    glUniform3fv(this->_textureProgram.uLightHouse_vs, 1, glm::value_ptr(this->_lightsMap["lightHouse"]->getPosition()));
    glUniform3fv(this->_textureProgram.uLightPuits_vs, 1, glm::value_ptr(this->_lightsMap["lightPuits"]->getPosition()));

    if (this->_color)
    {
        glUniform3fv(this->_textureProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.04)));
    }
    else
    {
        glUniform3fv(this->_textureProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.01)));
    }

    glm::mat4 viewMatrix = this->_viewMatrix.getViewMatrix();

    for (auto& obstacle : this->_obstacles)
    {
        obstacle.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->_materialMap, this->_color);
    };

    for (auto& cloud : this->_clouds)
    {
        cloud.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->_materialMap, this->_color);
        cloud.updatePosition(ctx);
    }

    this->_box.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->_materialMap, this->_color);
    this->_firefly.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->_materialMap, this->_color);
    this->_firefly.updatePosition(this->_viewMatrix, ctx);
}

void GameEnvironment::renderPanels()
{
    for (auto& panel : this->_panelsInfo)
    {
        if (panel.getDisplay())
            panel.draw(this->_viewMatrix.getViewMatrix(), this->_windowWidth, this->_windowHeight, this->_materialMap, this->_color);
    }
}

void GameEnvironment::inputManagement()
{
    if (this->_inputSystem.getZ())
        this->_viewMatrix.moveFront(this->_movementStrength, this->_obstacles);
    if (this->_inputSystem.getS())
        this->_viewMatrix.moveFront(-this->_movementStrength, this->_obstacles);
    if (this->_inputSystem.getQ())
        this->_viewMatrix.moveLeft(this->_movementStrength, this->_obstacles);
    if (this->_inputSystem.getD())
        this->_viewMatrix.moveLeft(-this->_movementStrength, this->_obstacles);

    this->_color = this->_inputSystem.getSpace();

    if (this->_inputSystem.getAlt() && this->_inputSystem.getIsMouseMoving())
    {
        this->_viewMatrix.rotateLeft(-(this->_inputSystem.getDeltaY()) * this->_rotationStrength);
        this->_viewMatrix.rotateUp(this->_inputSystem.getDeltaX() * this->_rotationStrength);
    }

    this->_inputSystem.setIsMouseMovingToFalse();
}

void GameEnvironment::colorManagement()
{
    double distance = glm::distance(this->_firefly.getPosition(), this->_magicPosition);
    if (distance < 0.5)
    {
        this->_inputSystem.setColorPossible(true);
    }
    else
    {
        this->_inputSystem.setColorPossible(false);
    }
}

void GameEnvironment::panelManagement()
{
    if (glm::distance(this->_firefly.getPosition(), this->_magicPosition) < 0.3)
    {
        if (!this->_panelsInfo[2].getDisplay() && !this->_panelsInfo[2].getHasBeenDislayed())
        {
            this->_panelsInfo[2].appears(this->_viewMatrix);
            this->_inputSystem.blockControls();
        }
    }
    if (this->_panelsInfo[0].getHasBeenDislayed() && !this->_panelsInfo[0].getDisplay() && !this->_panelsInfo[1].getDisplay() && !this->_panelsInfo[1].getHasBeenDislayed())
    {
        this->_panelsInfo[1].appears(this->_viewMatrix);
        this->_inputSystem.blockControls();
    }

    for (auto& panel : this->_panelsInfo)
    {
        if (panel.getDisplay())
        {
            if (this->_inputSystem.getEnter())
                panel.disapears();
        }
    }
}