#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class FreeflyCamera {
private:
    void computeDirectionVectors();

    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

public:
    FreeflyCamera();

    void moveLeft(float t);
    void moveFront(float t);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

    glm::vec3 getFront() const;
    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const;
};
