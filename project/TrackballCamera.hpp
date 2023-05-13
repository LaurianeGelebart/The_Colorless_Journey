#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace glimac {

class TrackballCamera {
public:
    TrackballCamera() : m_fDistance(5.f), m_fAngleX(0.f), m_fAngleY(0.f) {}

    void moveFront(float delta) {
        this->m_fDistance += delta ;  
    }
    void rotateLeft(float degrees){
        this->m_fAngleX += degrees ; 
    }
    void rotateUp(float degrees){
        this->m_fAngleY += degrees ; 
    }
    glm::mat4 getViewMatrix() const {
        glm::mat4 viewMatrix(1.f);

        viewMatrix = glm::translate(viewMatrix, glm::vec3(0.f, 0.f, -m_fDistance));
        viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
        viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));

        // std::cout << viewMatrix <<std::endl ;
        return viewMatrix;
    }
    

private:
    float m_fDistance ; 
    float m_fAngleX ; 
    float m_fAngleY ; 

};


}
