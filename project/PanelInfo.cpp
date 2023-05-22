#include "PanelInfo.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
    
PanelInfo::PanelInfo()
{}

PanelInfo::PanelInfo(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, PanelProgram& program)
:Object(model, lodModel, program) 
{
    this->_position = glm::vec3(0.0f, -1.0f, 0.0f); 
    this->_scale = 0.04;
}

bool PanelInfo::getDisplay()
{
    return this->_isDisplay; 
}

bool PanelInfo::getHasBeenDislayed()
{
    return this->_hasBeenDislayed; 
}

void PanelInfo::appears(const TrackballCamera& viewMatrix)
{
    glm::vec3 viewMatrixPosition = viewMatrix.getPosition(); 
    float angle = -viewMatrix.getAngleY();
    float a = sin(glm::radians(angle))*0.25; 
    float b = cos(glm::radians(angle))*0.35; 
    this->_position = glm::vec3((viewMatrixPosition.x+a) , 0.03, (viewMatrixPosition.z+b)); 
    this->_angleY = angle;
    this->_angleX = -viewMatrix.getAngleX();

    this->_isDisplay = true; 
    this->_hasBeenDislayed = true; 

}

void PanelInfo::disapears()
{
    this->_position.y = -1.0; 
    this->_isDisplay = false ; 
}

void PanelInfo::draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color)
{  
    this->_panelProgram->_Program.use() ; 

    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix = glm::rotate(MVMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));
    MVMatrix = glm::rotate(MVMatrix, glm::radians(this->_angleX), glm::vec3(1.f, 0.f, 0.f));

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    for(auto& face : this->_models[this->_lod] ){
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_panelProgram->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_panelProgram->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_panelProgram->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniform1i(this->_panelProgram->uTexture, materialMap[face.getName()].texture[color].getSlot());
    
        materialMap[face.getName()].texture[color].Bind();
        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());
        materialMap[face.getName()].texture[color].UnBind();


		glBindVertexArray(0) ;
    }
}