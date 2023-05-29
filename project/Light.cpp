#include "Light.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Light::Light() {}

Light::Light(glm::vec3 position)
: _environmentPosition(position)
{}

DirectionalLight::DirectionalLight(glm::vec3 position)
: Light(position)
{}

PointLight::PointLight(glm::vec3 position)
: Light(position)
{}

glm::vec3 Light::getPosition() const 
{
    return this->_position; 
}

void Light::setPosition(glm::vec3 position) 
{
    this->_environmentPosition = position; 
}

void PointLight::update(glm::mat4 viewMatrix)
{
    glm::mat4 LightMatrix = glm::translate(viewMatrix, this->_environmentPosition);
    this->_position = glm::vec3( (LightMatrix)*glm::vec4(0,0,0,1) );
}

void DirectionalLight::update(glm::mat4 viewMatrix)
{
    this->_position = glm::vec3( (viewMatrix)*glm::vec4(this->_environmentPosition, 0.f) ); 
}