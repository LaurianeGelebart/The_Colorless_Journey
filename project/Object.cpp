#include <cstdlib>
#include <vector>
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
}

Object::~Object(){
}

void Object::draw(const FreeflyCamera &ViewMatrix, const int window_width, const int window_height)
{  
    this->MVMatrix = ViewMatrix.getViewMatrix();
    this->MVMatrix = glm::scale(this->MVMatrix, glm::vec3(0.05));
    this->ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);

    glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix() ;
    //glm::mat4 MLightMatrix = glm::rotate(glm::mat4(1), ctx.time(), glm::vec3(0,1,0));
    // glm::vec3 lightPos = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,0,1) );
    //glm::vec3 lightDir = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,1,0) );
    glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) );

    glUniformMatrix4fv(this->_program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
    glUniformMatrix4fv(this->_program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(this->ProjMatrix * this->MVMatrix));

    this->MVMatrix = glm::translate(this->MVMatrix, glm::vec3(this->_position));
    glUniformMatrix4fv(this->_program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(this->MVMatrix));

    glUniform1f(this->_program.uShininess, 0.5);
    glUniform3fv(this->_program.uKd, 1, glm::value_ptr(glm::vec3(0.2,0.5,0.5)));
    glUniform3fv(this->_program.uKs, 1, glm::value_ptr(glm::vec3(0.1,0.2,0.2)));
    // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos));
    glUniform3fv(this->_program.uLightDir_vs, 1, glm::value_ptr(lightDir));
    glUniform3fv(this->_program.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));


    glDrawArrays(GL_TRIANGLES, 0, this->_model.getVertextCount());
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