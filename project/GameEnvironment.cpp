#include "p6/p6.h"
#include "GameEnvironment.hpp"

GameEnvironment::GameEnvironment(int  windowWidth, int  windowHeight)
: _windowWidth(windowWidth), _windowHeight(windowHeight)
{}

void GameEnvironment::initScene()
{
    initObjectModel();
    initBoids();
    initObstacles();
    initClouds();
    initWanderer();
    initContent();
    initPanels();
    // initFBO();
}

void GameEnvironment::initFBO()
{
	// Framebuffer for Shadow Map
	// glGenFramebuffers(1, &shadowMapFBO);

	// // Texture for Shadow Map FBO
	// int shadowMapWidth = 2048, shadowMapHeight = 2048;
	// glGenTextures(1, &shadowMap);
	// glBindTexture(GL_TEXTURE_2D, shadowMap);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// // Prevents darkness outside the frustrum
	// float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	// glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	// glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	// // Needed since we don't touch the color buffer
	// glDrawBuffer(GL_NONE);
	// glReadBuffer(GL_NONE);
	// glBindFramebuffer(GL_FRAMEBUFFER, 0);
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


void GameEnvironment::initObjectModel()
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

void GameEnvironment::initBoids()
{
    for(int i=0 ; i<this->_ihm.getNbBoids() ; i++){
         Boid b(this->_sphere, this->_sphere, this->_textureProgram, this->_magicPos) ;
         this->boids.push_back(b);
    }
}

void GameEnvironment::initObstacles()
{
    this->obstacles.push_back(Obstacle(this->_house, this->_sphere, this->_textureProgram, glm::vec3(-1.1, 0.0, -0.0))) ;
    this->obstacles.push_back(Obstacle(this->_puit, this->_sphere, this->_textureProgram, glm::vec3(1.0, 0.0, 1.1))) ;
    this->obstacles.push_back(Obstacle(this->_rail, this->_rail, this->_textureProgram, glm::vec3(-1.8, 0.0, 1.8))) ;
    this->obstacles.push_back(Obstacle(this->_rocks, this->_sphere, this->_textureProgram, glm::vec3(-1.2, 0.0, -1.1))) ;
    this->obstacles.push_back(Obstacle(this->_barel, this->_sphere, this->_textureProgram, glm::vec3(-0.4, 0.0, 0.0))) ;
    this->obstacles.push_back(Obstacle(this->_magic, this->_sphere, this->_textureProgram, this->_magicPos)) ;
    this->obstacles.push_back(Obstacle(this->_panneau, this->_sphere, this->_textureProgram, glm::vec3(0.3, 0.0, 0.3))) ;

    for(int i=this->obstacles.size(); i < this->_ihm.getNbObstacles(); i++){
        float j = p6::random::number(); 
        if(j < 0.25) {
            this->obstacles.push_back(Obstacle(this->_fir1, this->_sphere, this->_textureProgram));
        } else if(j < 0.5) {
            this->obstacles.push_back(Obstacle(this->_fir2, this->_sphere, this->_textureProgram));
        } else if (j < 0.75){
            this->obstacles.push_back(Obstacle(this->_fir3, this->_sphere, this->_textureProgram));
        } else if(j < 0.90) {
            this->obstacles.push_back(Obstacle(this->_mushroom1, this->_sphere, this->_textureProgram));
        } else {
            this->obstacles.push_back(Obstacle(this->_mushroom2, this->_sphere, this->_textureProgram));
        }
    }

  }

void GameEnvironment::initClouds()
{
    for(int i=0 ; i<3 ; i++){
         Cloud c(this->_cloud, this->_sphere, this->_textureProgram) ;
         this->clouds.push_back(c);
     }    
}

void GameEnvironment::initWanderer()
{
    this->gaspard = Wanderer(this->_magic, this->_sphere, this->_textureProgram);
}

void GameEnvironment::initContent()
{
    this->box = Content(this->_content, this->_sphere, this->_textureProgram) ;
}

void GameEnvironment::initPanels()
{
    this->panelsInfo.push_back(PanelInfo(this->_panelBeginning, this->_panelColor, this->_panelProgram));
    this->panelsInfo.push_back(PanelInfo(this->_panelColor, this->_panelBeginning, this->_panelProgram));
    this->panelsInfo[0].appears(this->_ViewMatrix);
}

void GameEnvironment::render(p6::Context &ctx)
{

    if (glm::distance(this->gaspard.getPosition(), this->_magicPos) < 0.5 ) {    
        if( !this->panelsInfo[1].getDisplay() && !this->panelsInfo[1].getHasBeenDislayed() ){
            this->panelsInfo[1].appears(this->_ViewMatrix);
            this->_alt = false ;
            mouseMoveManagement(ctx);
        }
    }

    glm::mat4 viewMatrix = this->_ViewMatrix.getViewMatrix();

    for(auto& boid : this->boids){
        boid.checkLOD(this->gaspard.getPosition());
        boid.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
        boid.collision(this->boids, this->obstacles, this->_ihm) ;
        boid.update_position() ;
    };

    for(auto& obstacle : this->obstacles){
        obstacle.checkLOD(this->gaspard.getPosition());
        obstacle.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    };

    for(auto& cloud : this->clouds){
        // cloud.checkLOD(this->gaspard.getPosition());
        cloud.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
        cloud.update_position(ctx) ;
    }

    this->box.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    this->gaspard.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    this->gaspard.update_position(this->_ViewMatrix); 

    for(auto& panel : this->panelsInfo){
        if (panel.getDisplay()) panel.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    }
    // std::cout << " character " << this->gaspard[0].getPosition().x << " - "  << this->gaspard[0].getPosition().y << " - " << this->gaspard[0].getPosition().z << "\n";

    this->_ihm.draw();


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
    if(isMenu){
        ctx.key_pressed = [this, nbMenu](const p6::Key& key) {
            if (key.physical == GLFW_KEY_ENTER || key.physical == GLFW_KEY_SPACE) {
                this->panelsInfo[nbMenu].disapears();
                this->_alt = true ;
                // mouseMoveManagement(ctx);
            }
        };
    }
    else {
        // std::cout << "else ? " << this->_alt << "\n";
        ctx.key_pressed = [this](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W) this->_Z = true;
            if (key.physical == GLFW_KEY_S) this->_S = true;
            if (key.physical == GLFW_KEY_A) this->_Q = true;
            if (key.physical == GLFW_KEY_D) this->_D = true;
            if (key.physical == GLFW_KEY_LEFT_ALT) this->_alt = !this->_alt ;
            if (key.physical == GLFW_KEY_SPACE) colorManagement();
        };
        ctx.key_released = [this](const p6::Key& key) {
            if (key.physical == GLFW_KEY_W) this->_Z = false;
            if (key.physical == GLFW_KEY_S) this->_S = false;
            if (key.physical == GLFW_KEY_A) this->_Q = false;
            if (key.physical == GLFW_KEY_D) this->_D = false;
        };

        mouseMoveManagement(ctx);
    }
}

void GameEnvironment::colorManagement()
{
    double distance = glm::distance(this->gaspard.getPosition(), this->_magicPos);

    if(distance < 0.5) {
        this->_color = !this->_color;
    }
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

void GameEnvironment::addOrRemoveBoids()
{
    int nbBoids = this->boids.size();

    if (nbBoids < this->_ihm.getNbBoids()){
        for(int i=0 ; i< this->_ihm.getNbBoids()-nbBoids ; i++){
            Boid b(this->_sphere, this->_sphere, this->_textureProgram, this->_magicPos) ;
            this->boids.push_back(b);
        }
    }
    else if (nbBoids > this->_ihm.getNbBoids()){
        for(int i=0 ; i< nbBoids-this->_ihm.getNbBoids() ; i++){
            this->boids.pop_back();
        }
    }
}

void GameEnvironment::addOrRemoveObstacles()
{
    int nbObstacles = obstacles.size();

    if (nbObstacles < this->_ihm.getNbObstacles()){
        for(int i=0 ; i< this->_ihm.getNbObstacles() ; i++){
            Obstacle o(this->_fir1, this->_sphere, this->_textureProgram) ;
            obstacles.push_back(o);
        }
    }
    else if (nbObstacles > this->_ihm.getNbObstacles()){
        for(int i=0 ; i< nbObstacles-this->_ihm.getNbObstacles() ; i++){
            obstacles.pop_back();
        }
    }
}
