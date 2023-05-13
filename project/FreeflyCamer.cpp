#include "FreeflyCamera.hpp"

#include <glm/gtc/constants.hpp>

FreeflyCamera::FreeflyCamera() :
    m_Position(0.f, 0.1, 1.5),
    m_fPhi(glm::pi<float>()),
    m_fTheta(0.f)
{
    computeDirectionVectors();
}

void FreeflyCamera::moveLeft(float t)
{
    m_Position += t * m_LeftVector;
}

void FreeflyCamera::moveFront(float t)
{
    m_Position += t * m_FrontVector;
}

void FreeflyCamera::rotateLeft(float degrees)
{
    m_fPhi += glm::radians(degrees);
    computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees)
{
    m_fTheta += glm::radians(degrees);
    computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const
{
    return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

glm::vec3 FreeflyCamera::getPosition() const
{
    return this->m_Position;
}

void FreeflyCamera::computeDirectionVectors()
{
    m_FrontVector = glm::vec3(
        glm::cos(m_fTheta) * glm::sin(m_fPhi),
        glm::sin(m_fTheta),
        glm::cos(m_fTheta) * glm::cos(m_fPhi)
    );
    m_LeftVector = glm::vec3(
        glm::sin(m_fPhi + glm::half_pi<float>()),
        0,
        glm::cos(m_fPhi + glm::half_pi<float>())
    );

    m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
}

glm::vec3 FreeflyCamera::getFront() const {
    // Calculer la direction vers laquelle la caméra est orientée en utilisant la formule de la sphère
    // https://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates
    float sinPhi = sin(m_fPhi);
    float cosPhi = cos(m_fPhi);
    float sinTheta = sin(m_fTheta);
    float cosTheta = cos(m_fTheta);
    glm::vec3 dir(cosTheta * sinPhi, sinTheta, cosTheta * cosPhi);

    // Normaliser le vecteur de direction
    return glm::normalize(dir);
}