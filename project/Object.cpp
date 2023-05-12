#include <cstdlib>
#include <vector>
#include <map>
#include "glm/gtc/random.hpp"
#include <fstream>
#include <iostream>

#include "FreeflyCamera.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "p6/p6.h"
#include "Object.hpp"



Object::Object(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
 :  _facesGroup(facesGroup), _program(program)
{}

Object::~Object(){}


Vec Object::get_position() const
{
    return this->_position ; 
}

void Object::draw(const FreeflyCamera &ViewMatrix, const int window_width, const int window_height, std::map<std::string, Material>& materialMap)
{  
    this->_program.m_Program.use() ; 

    glm::mat4 MVMatrix = ViewMatrix.getViewMatrix();
    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix = glm::translate(MVMatrix, glm::vec3(this->_position));

    // std::cout<< this->texture << "\n"; 
    
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)window_width / (float)window_height, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glm::mat4 VLightMatrix = ViewMatrix.getViewMatrix();
    //glm::mat4 MLightMatrix = glm::rotate(glm::mat4(1), ctx.time(), glm::vec3(0,1,0));
    // glm::vec3 lightPos = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,0,1) );
    //glm::vec3 lightDir = glm::vec3( (MLightMatrix*VLightMatrix)*glm::vec4(1,1,1,0) );
    glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) );


    for(auto face : this->_facesGroup ){
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_program.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
       
       if(materialMap[face.getName()].texture._slot >= 0){
            glUniform1i(this->_program.uTexture, materialMap[face.getName()].texture._slot);
       }else{
            glUniform1i(this->_program.uTexture, 0);
       }

        glUniform1f(this->_program.uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program.uKd, 1, glm::value_ptr(materialMap[face.getName()].Kd));
        glUniform3fv(this->_program.uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));
        // glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_program.uLightDir_vs, 1, glm::value_ptr(lightDir));
        glUniform3fv(this->_program.uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));

// std::cout << face.getName() << " - " << materialMap[face.getName()].texture._slot << "\n";

        materialMap[face.getName()].texture.Bind();

        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());

        materialMap[face.getName()].texture.UnBind();


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

