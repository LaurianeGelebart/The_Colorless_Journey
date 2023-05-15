#include <cstdlib>
#include <vector>
#include <map>
#include "glm/gtc/random.hpp"
#include <fstream>
#include <iostream>

#include "FreeflyCamera.hpp"
#include "TrackballCamera.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "p6/p6.h"
#include "Object.hpp"



Object::Object(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
 :  _facesGroup(facesGroup), _program(program)
{}

// Object::~Object(){}


Vec Object::getPosition() const
{
    return this->_position ; 
}

void Object::draw(const TrackballCamera &ViewMatrix, const int window_width, const int window_height, std::map<std::string, Material>& materialMap, Vec ArpenteurPos, int color)
{  
    this->_program._Program.use() ; 

    glm::mat4 MVMatrix = ViewMatrix.getViewMatrix();
    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix = glm::rotate(MVMatrix, glm::radians(this->_angle), glm::vec3(0.f, 1.f, 0.f));

// std::cout << this->_position.x << " - " << this->_position.y << " - " << this->_position.z << "\n";
    
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix();
    glm::vec3 lightPos = glm::vec3( (VLightMatrix)*glm::vec4(1,1,0,1) );
    glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) );
    
    glm::mat4 MLightMatrix = glm::translate(glm::mat4(1.0), ViewMatrix.getPosition());
    glm::vec3 lightCharacter = glm::vec3( (MLightMatrix)*glm::vec4(1,1,0,1) );


    for(auto face : this->_facesGroup ){
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
       
    //    std::cout << face.getName() << " - " << materialMap[face.getName()].texture[color].getSlot() << "\n";
        glUniform1i(this->_program.uTexture, materialMap[face.getName()].texture[color].getSlot());
    
        glUniform1f(this->_program.uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program.uKd, 1, glm::value_ptr(materialMap[face.getName()].Kd));
        glUniform3fv(this->_program.uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));
        glUniform3fv(this->_program.uLightPos_vs, 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_program.uLightDir_vs, 1, glm::value_ptr(lightDir));
        glUniform3fv(this->_program.uLightCharacter_vs, 1, glm::value_ptr(lightCharacter));
        glUniform3fv(this->_program.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));

// std::cout << face.getName() << " - " << face.getVertextCount() << "\n";

        materialMap[face.getName()].texture[color].Bind();

        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());

        materialMap[face.getName()].texture[color].UnBind();


		glBindVertexArray(0) ;
    }
}


void Object::deleteVAO_VBO()
{
    for(auto face : this->_facesGroup ){
        GLuint vbo = face.getVBO(); 
        GLuint ibo = face.getIBO(); 
        GLuint vao = face.getVAO(); 
        glDeleteBuffers(0, &vbo);
        glDeleteBuffers(0, &ibo); 
        glDeleteVertexArrays(0, &vao);
    }
}

