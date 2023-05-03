#include <cstdlib>
#include <vector>
#include "glm/gtc/random.hpp"
#include <fstream>
#include <iostream>

#include "glimac/FreeflyCamera.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "p6/p6.h"
#include "Object.hpp"



Object::Object(const ObjModel& model, const ObjectProgram& program)
 : _model(model), _program(program), _vbo(0)
{
    createVBO(); 
    //  wood = p6::load_image_buffer("./assets/textures/wood.png") ;  
    // //  rock = p6::load_image_buffer("./assets/textures/rock.png") ;  
    // // stele = p6::load_image_buffer("./assets/textures/stele.png") ;  
    //  brick = p6::load_image_buffer("./assets/textures/red_brick_draw.png") ;  

    // GLuint     wood_texture;
    // glGenTextures(1, &wood_texture);
    // glBindTexture(GL_TEXTURE_2D, wood_texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wood.width(), wood.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, wood.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);

    // GLuint     brick_texture;
    // glGenTextures(1, &brick_texture);
    // glBindTexture(GL_TEXTURE_2D, brick_texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, brick.width(), brick.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, brick.data());
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    
}

Object::~Object(){
}

void Object::draw(const FreeflyCamera &ViewMatrix, const int window_width, const int window_height)
{  
    this->_program.m_Program.use() ; 
    
    this->_MVMatrix = ViewMatrix.getViewMatrix();
    // std::cout << this->_MVMatrix[0].x << "-" << this->_MVMatrix[0].y << "\n"; 

    this->_MVMatrix = glm::scale(this->_MVMatrix, glm::vec3(0.05));
    this->_ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);

    glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix() ;
    //glm::mat4 MLightMatrix = glm::rotate(glm::mat4(1), ctx.time(), glm::vec3(0,1,0));
    // glm::vec3 lightPos = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,0,1) );
    //glm::vec3 lightDir = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,1,0) );
    glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) );

    this->_MVMatrix = glm::translate(this->_MVMatrix, glm::vec3(this->_position));
    
    glUniformMatrix4fv(this->_program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(this->_MVMatrix))));
    glUniformMatrix4fv(this->_program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(this->_ProjMatrix * this->_MVMatrix));
    glUniformMatrix4fv(this->_program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(this->_MVMatrix));

    glUniform1f(this->_program.uShininess, 0.5);
    glUniform3fv(this->_program.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5)));
    glUniform3fv(this->_program.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2)));
    // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos));
    glUniform3fv(this->_program.uLightDir_vs, 1, glm::value_ptr(lightDir));
    glUniform3fv(this->_program.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));



    glUniform1i(this->_program.uTexture1, 0);
    glUniform1i(this->_program.uTexture2, 0);


    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, wood_texture);
    // // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wood_texture.width(), wood_texture.height(), 0, GL_RGBA, GL_FLOAT, wood_texture->data()  ) ;
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, brick_texture);

    glDrawArrays(GL_TRIANGLES, 0, this->_model.getVertextCount());

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, 0);
}


Vec Object::get_position() const
{
    return this->_position ; 
}

void Object::createVBO()
{
    glGenBuffers(1, &this->_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    
    std::vector<float> vertices = this->_model.getVertextData();

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
}