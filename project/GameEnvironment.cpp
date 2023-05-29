#include "p6/p6.h"
#include "GameEnvironment.hpp"
#include "glm/gtc/type_ptr.hpp"

GameEnvironment::GameEnvironment(int  windowWidth, int  windowHeight)
: _windowWidth(windowWidth), _windowHeight(windowHeight)
{
}

void GameEnvironment::initScene()
{
    this->_initSystem.initObjectModel(this->materialMap);
    this->_initSystem.initBoids(this->boids, this->_boidProgram, this->_magicPosition);
    this->_initSystem.initObstacles(this->obstacles, this->_textureProgram, this->_magicPosition, this->_housePosition, this->_puitsPosition);
    this->_initSystem.initClouds(this->clouds, this->_textureProgram);
    this->_initSystem.initWanderer(this->gaspard, this->_textureProgram);
    this->_initSystem.initContent(this->box, this->_textureProgram);
    this->_initSystem.initPanels(this->panelsInfo, this->_panelProgram, this->_ViewMatrix);
    this->_initSystem.initLighting(this->_lightsMap, this->_magicPosition, this->_puitsPosition, this->_housePosition, this->gaspard.getPosition());
    this->_shadowSystem.initFBO();
}

void GameEnvironment::deleteScene()
{
    for(auto& obstacle : this->obstacles){
        obstacle.deleteVAO_VBO() ; 
    }
    for(auto& boid : this->boids){
        boid.deleteVAO_VBO() ; 
    }
    for(auto& cloud : this->clouds){
        cloud.deleteVAO_VBO() ; 
    }
    gaspard.deleteVAO_VBO() ; 
    box.deleteVAO_VBO() ; 
    glfwTerminate();
}

void GameEnvironment::panelManagement(p6::Context &ctx)
{
    if (glm::distance(this->gaspard.getPosition(), this->_magicPosition) < 0.3 ) {    
        if( !this->panelsInfo[2].getDisplay() && !this->panelsInfo[2].getHasBeenDislayed() ){
            this->panelsInfo[2].appears(this->_ViewMatrix);
            this->_alt = false ;
            this->_Z = false ;
            this->_Q = false ;
            this->_S = false ;
            this->_D = false ;
            mouseMoveManagement(ctx);
        }
    }
    if ( this->panelsInfo[0].getHasBeenDislayed() && !this->panelsInfo[0].getDisplay() && 
         !this->panelsInfo[1].getDisplay() && !this->panelsInfo[1].getHasBeenDislayed() )
         {
            this->panelsInfo[1].appears(this->_ViewMatrix);
            this->_alt = false ;
            this->_Z = false ;
            this->_Q = false ;
            this->_S = false ;
            this->_D = false ;
            mouseMoveManagement(ctx);
        }
}

void GameEnvironment::render(p6::Context &ctx)
{

    this->_initSystem.addOrRemoveBoids(this->boids, this->_boidProgram, this->_magicPosition) ;
    this->_initSystem.addOrRemoveObstacles(this->obstacles, this->_textureProgram) ;

    this->_initSystem._ihm.draw();


    this->_lightsMap["lightCharacter"]->setPosition(this->gaspard.getPosition());

    for(auto& light : this->_lightsMap){
        light.second->update(this->_ViewMatrix.getViewMatrix());
    }

    // for(auto& obstacle : this->obstacles){
    //     this->_shadowSystem.renderShadow(obstacle, this->_ViewMatrix.getPosition(), lightDir);
    // }
    
    
    renderBoids(ctx); 
    renderObjects(ctx); 
    renderPanels(ctx); 
   
}

void GameEnvironment::renderBoids()
{
    this->_boidProgram._Program.use() ;
  
    glUniform3fv(this->_boidProgram.uLightPos_vs, 1, glm::value_ptr(this->_lightsMap["lightMagic"]->getPosition()));
    glUniform3fv(this->_boidProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.1)));

    for(auto& boid : this->boids){
        boid.checkLOD(this->gaspard.getPosition());
        boid.draw(this->_ViewMatrix.getViewMatrix(), this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
        boid.collision(this->boids, this->obstacles, this->_initSystem._ihm) ;
        boid.updatePosition() ;
    };
}

void GameEnvironment::renderObjects(p6::Context &ctx)
{
    this->_textureProgram._Program.use() ; 

    glUniform3fv(this->_textureProgram.uLightMagic_vs, 1, glm::value_ptr(this->_lightsMap["lightMagic"]->getPosition()));
    glUniform3fv(this->_textureProgram.uLightCharacter_vs, 1, glm::value_ptr(this->_lightsMap["lightCharacter"]->getPosition()));
    
    if(this->_color){
        glUniform3fv(this->_textureProgram.uLightDir_vs, 1, glm::value_ptr(this->_lightsMap["lightDir"]->getPosition()));
        glUniform3fv(this->_textureProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.06)));
    }
    else{
        glUniform3fv(this->_textureProgram.uLightPuits_vs, 1, glm::value_ptr(this->_lightsMap["lightPuits"]->getPosition()));
        glUniform3fv(this->_textureProgram.uLightHouse_vs, 1, glm::value_ptr(this->_lightsMap["lightHouse"]->getPosition()));
        glUniform3fv(this->_textureProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.01)));
    }

    glm::mat4 viewMatrix = this->_ViewMatrix.getViewMatrix();
    
    for(auto& obstacle : this->obstacles){
        obstacle.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    };

    for(auto& cloud : this->clouds){
        cloud.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
        cloud.updatePosition(ctx) ;
    }

    this->box.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    this->gaspard.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    this->gaspard.updatePosition(this->_ViewMatrix, ctx); 
}

void GameEnvironment::renderPanels()
{
    for(auto& panel : this->panelsInfo){
        if (panel.getDisplay()) panel.draw(this->_ViewMatrix.getViewMatrix(), this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    }
}

void GameEnvironment::inputManagement(p6::Context &ctx)
{
    bool isMenu = false ; 
    int nbMenu; 
    for(size_t i=0 ; i<this->panelsInfo.size(); i++){
        if (this->panelsInfo[i].getDisplay()) {
            isMenu = true ; 
            nbMenu = i ; 
        }
    }
  
    ctx.key_pressed = [this, isMenu, nbMenu](const p6::Key& key) {
        if(isMenu){
            if (key.physical == GLFW_KEY_ENTER || key.physical == GLFW_KEY_SPACE) {
                this->panelsInfo[nbMenu].disapears();
                this->_alt = true ;
            }
        }
        else{
            if (key.physical == GLFW_KEY_W) this->_Z = true;
            if (key.physical == GLFW_KEY_S) this->_S = true;
            if (key.physical == GLFW_KEY_A) this->_Q = true;
            if (key.physical == GLFW_KEY_D) this->_D = true;
            if (key.physical == GLFW_KEY_LEFT_ALT) this->_alt = !this->_alt ;
            if (key.physical == GLFW_KEY_SPACE) colorManagement();
        }
    };

    ctx.key_released = [this, isMenu](const p6::Key& key) {
        if(!isMenu){
            if (key.physical == GLFW_KEY_W) this->_Z = false;
            if (key.physical == GLFW_KEY_S) this->_S = false;
            if (key.physical == GLFW_KEY_A) this->_Q = false;
            if (key.physical == GLFW_KEY_D) this->_D = false;
        }
    };

    mouseMoveManagement(ctx);
    
}

void GameEnvironment::mouseMoveManagement(p6::Context &ctx)
{
    if (this->_alt) {
        ctx.mouse_moved = [&](p6::MouseMove data) {
            (this->_ViewMatrix).rotateLeft(-data.delta.y * this->_rotationStrength);
            (this->_ViewMatrix).rotateUp(data.delta.x * this->_rotationStrength);
        };
    } else {
        ctx.mouse_moved = [&](p6::MouseMove data) {};
    }
}


void GameEnvironment::cameraManagement()
{
    if (_Z) this->_ViewMatrix.moveFront(this->_movementStrength, this->obstacles);
    if (_S) this->_ViewMatrix.moveFront(-this->_movementStrength, this->obstacles);
    if (_Q) this->_ViewMatrix.moveLeft(this->_movementStrength, this->obstacles);
    if (_D) this->_ViewMatrix.moveLeft(-this->_movementStrength, this->obstacles);
}

void GameEnvironment::colorManagement()
{
    double distance = glm::distance(this->gaspard.getPosition(), this->_magicPosition);

    if(distance < 0.5) {
        this->_color = !this->_color;
    }
}