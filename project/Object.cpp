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

Object::Object(){}

// Object::~Object(){}


glm::vec3 Object::getPosition() const
{
    return this->_position ; 
}

void Object::draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color)
{  
    this->_program->_Program.use() ; 

    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix = glm::rotate(MVMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));

    // std::cout << this->_position.x << " - " << this->_position.y << " - " << this->_position.z << "\n";
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


// light 
    glm::mat4 VLightMatrix = ViewMatrix;
    glm::vec3 lightPos = glm::vec3( (VLightMatrix)*glm::vec4(1,1,0,1) );
    glm::vec3 lightDir = glm::vec3( (VLightMatrix)*glm::vec4(1,1,1,0) ); 
    // std::cout << wandererPos.x/10.f << " - "  << wandererPos.y << " - " << wandererPos.z/10.f << "\n";
    glm::mat4 MLightMatrix = glm::translate(glm::mat4(1.0), glm::vec3(wandererPos));
    glm::vec3 lightCharacter = glm::vec3( (MLightMatrix)*glm::vec4(1,1,0,1) );


//shadow part
    // glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	// glm::mat4 lightView = glm::lookAt(20.0f * lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// glm::mat4 lightProjection = orthgonalProjection * lightView;

	// shadowMapProgram.Activate();
	// glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
// ossekour 


    for(auto& face : this->_models[this->_lod] ){
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_program->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_program->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_program->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
       
    //    std::cout << face.getName() << " - " << materialMap[face.getName()].texture[color].getSlot() << "\n";
        glUniform1i(this->_program->uTexture, materialMap[face.getName()].texture[color].getSlot());
    
        glUniform1f(this->_program->uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program->uKd, 1, glm::value_ptr(materialMap[face.getName()].Kd));
        glUniform3fv(this->_program->uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));
        glUniform3fv(this->_program->uLightPos_vs, 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_program->uLightDir_vs, 1, glm::value_ptr(lightDir));
        glUniform3fv(this->_program->uLightCharacter_vs, 1, glm::value_ptr(lightCharacter));
        glUniform3fv(this->_program->uLightIntensity, 1, glm::value_ptr(glm::vec3(0.2)));

// std::cout << face.getName() << " - " << face.getVertextCount() << "\n";

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

