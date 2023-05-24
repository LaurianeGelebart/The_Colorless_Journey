#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

#include "FreeflyCamera.hpp"
#include "TrackballCamera.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"

#include "p6/p6.h"
#include "Object.hpp"



Object::Object(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program)
 : _program(&program)
{
    _models.push_back(model);
    _models.push_back(lodModel);
    // ShadowMapProgram
}

Object::Object(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, PanelProgram& program)
 : _panelProgram(&program)
{
    _models.push_back(model);
    _models.push_back(lodModel);
}

Object::Object(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ColorProgram& program)
 : _boidProgram(&program)
{
    _models.push_back(model);
    _models.push_back(lodModel);
}

Object::Object(){}

// Object::~Object(){}


glm::vec3 Object::getPosition() const
{
    return this->_position ; 
}

void Object::draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color)
{  

    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix = glm::rotate(MVMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glUniformMatrix4fv(this->_program->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(this->_program->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(this->_program->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));

    for(auto& face : this->_models[this->_lod] ){
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);
         
        glUniform1i(this->_program->uTexture, materialMap[face.getName()].texture[color].getSlot());
        glUniform1f(this->_program->uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program->uKd, 1, glm::value_ptr(materialMap[face.getName()].Kd));
        glUniform3fv(this->_program->uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));

        materialMap[face.getName()].texture[color].Bind();
        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());
        materialMap[face.getName()].texture[color].UnBind();

		glBindVertexArray(0) ;
    }
}

void Object::checkLOD(glm::vec3 gaspardPosition)
{
    double distance = glm::distance(gaspardPosition, this->_position);
    this->_lod = (distance > 1.7) ? 1 : 0;
}

void Object::deleteVAO_VBO()
{
    for (size_t i = 0; i < this->_models.size(); i++) {
        for (auto& face : this->_models[i]) {
            GLuint vbo = face.getVBO(); 
            GLuint ibo = face.getIBO(); 
            GLuint vao = face.getVAO(); 
            glDeleteBuffers(0, &vbo);
            glDeleteBuffers(0, &ibo); 
            glDeleteVertexArrays(0, &vao);
        }
    }
}

