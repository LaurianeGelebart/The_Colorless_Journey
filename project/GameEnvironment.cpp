#include "p6/p6.h"
#include "GameEnvironment.hpp"
#include "glm/gtc/type_ptr.hpp"

GameEnvironment::GameEnvironment(int  windowWidth, int  windowHeight)
: _windowWidth(windowWidth), _windowHeight(windowHeight)
{
}

void GameEnvironment::initScene()
{
    this->_initGame.initObjectModel(this->materialMap);
    this->_initGame.initBoids(this->boids, this->_boidProgram, this->_magicPosition);
    this->_initGame.initObstacles(this->obstacles, this->_textureProgram, this->_magicPosition, this->_housePosition, this->_puitsPosition);
    this->_initGame.initClouds(this->clouds, this->_textureProgram);
    this->_initGame.initWanderer(this->gaspard, this->_textureProgram);
    this->_initGame.initContent(this->box, this->_textureProgram);
    this->_initGame.initPanels(this->panelsInfo, this->_panelProgram, this->_ViewMatrix);
    initFBO();
}

void GameEnvironment::initFBO()
{
	glGenFramebuffers(1, &_shadowMapFBO);

	// Texture for Shadow Map FBO
	glGenTextures(1, &_shadowMap);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// Prevents darkness outside the frustrum
	float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	glBindFramebuffer(GL_FRAMEBUFFER, _shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowMap, 0);
	// Needed since we don't touch the color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
        if( !this->panelsInfo[1].getDisplay() && !this->panelsInfo[1].getHasBeenDislayed() ){
            this->panelsInfo[1].appears(this->_ViewMatrix);
            this->_alt = false ;
            this->_Z = false ;
            this->_Q = false ;
            this->_S = false ;
            this->_D = false ;
            mouseMoveManagement(ctx);
        }
    }
}

void GameEnvironment::render(p6::Context &ctx)
{

    this->_initGame.addOrRemoveBoids(this->boids, this->_boidProgram, this->_magicPosition) ;
    this->_initGame.addOrRemoveObstacles(this->obstacles, this->_textureProgram) ;

    glm::mat4 viewMatrix = this->_ViewMatrix.getViewMatrix();

// light 
    glm::mat4 VLightMatrix = viewMatrix;
    // glm::vec3 lightPos = glm::vec3( (VLightMatrix)*glm::vec4(0,1.5,0,1) );
    glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) ); 

    glm::mat4 MLightMatrix = glm::translate(VLightMatrix, this->_magicPosition);
    glm::vec3 lightMagic = glm::vec3( (MLightMatrix)*glm::vec4(0,0,0,1) );

    glm::mat4 PLightMatrix = glm::translate(VLightMatrix, this->_puitsPosition);
    glm::vec3 lightPuits = glm::vec3( (PLightMatrix)*glm::vec4(0,0,0,1) );

    glm::mat4 HLightMatrix = glm::translate(VLightMatrix, this->_housePosition);
    glm::vec3 lightHouse = glm::vec3( (HLightMatrix)*glm::vec4(0,0,0,1) );

    glm::mat4 CLightMatrix = glm::translate(VLightMatrix, this->gaspard.getPosition());
    glm::vec3 lightCharacter = glm::vec3( (CLightMatrix)*glm::vec4(0,0,0,1) );


    // glViewport(0, 0, shadowMapWidth, shadowMapHeight);
    // glBindFramebuffer(GL_FRAMEBUFFER, _shadowMapFBO);

    // float near_plane = 1.0f, far_plane = 7.5f;
    // glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);  
    // glm::mat4 lightView = glm::lookAt(this->_ViewMatrix.getPosition(), 
    //                                 glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) ), 
    //                                 glm::vec3( 0.0f, 1.0f,  0.0f));  

    // glm::mat4 lightSpaceMatrix = lightProjection * lightView; 

   
    // this->_shadowProgram._Program.use() ;
    // glUniformMatrix4fv(ulightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

    // glViewport(0, 0, shadowMapWidth, shadowMapHeight);
    // glBindFramebuffer(GL_FRAMEBUFFER, this->_shadowMapFBO);
    //     glClear(GL_DEPTH_BUFFER_BIT);
    //     RenderScene(this->_shadowProgram);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0); 

//shadow part
    // glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	// glm::mat4 lightView = glm::lookAt(20.0f * lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// glm::mat4 lightProjection = orthgonalProjection * lightView;

	// shadowMapProgram.Activate();
	// glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
// ossekour 


// ------------------------ BOIDS -----------------------//  
    
    this->_boidProgram._Program.use() ;
  
    glUniform3fv(this->_boidProgram.uLightPos_vs, 1, glm::value_ptr(lightMagic));
    glUniform3fv(this->_boidProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.1)));

    for(auto& boid : this->boids){
        boid.checkLOD(this->gaspard.getPosition());
        boid.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
        boid.collision(this->boids, this->obstacles, this->_initGame._ihm) ;
        boid.updatePosition() ;
    };

   
// ------------------------ OBJECT -----------------------//  
    
    this->_textureProgram._Program.use() ; 

    glUniform3fv(this->_textureProgram.uLightMagic_vs, 1, glm::value_ptr(lightMagic));
    glUniform3fv(this->_textureProgram.uLightCharacter_vs, 1, glm::value_ptr(lightCharacter));
    

    if(this->_color){
        // glUniform3fv(this->_textureProgram.uLightPos_vs, 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_textureProgram.uLightDir_vs, 1, glm::value_ptr(lightDir));
        glUniform3fv(this->_textureProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.06)));
    }
    else{
        glUniform3fv(this->_textureProgram.uLightPuits_vs, 1, glm::value_ptr(lightPuits));
        glUniform3fv(this->_textureProgram.uLightHouse_vs, 1, glm::value_ptr(lightHouse));
        glUniform3fv(this->_textureProgram.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.01)));
    }
    

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

    for(auto& panel : this->panelsInfo){
        if (panel.getDisplay()) panel.draw(viewMatrix, this->_windowWidth, this->_windowHeight, this->materialMap, this->gaspard.getPosition(), this->_color);
    }

    this->_initGame._ihm.draw();

// glBindFramebuffer(GL_FRAMEBUFFER, 0);

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

void GameEnvironment::colorManagement()
{
    double distance = glm::distance(this->gaspard.getPosition(), this->_magicPosition);

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
