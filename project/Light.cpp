#include "Light.hpp"
#include "glm/gtc/matrix_transform.hpp"

Light::Light() = default;

Light::Light(const glm::vec3& position)
    : _environmentPosition(position)
{}

DirectionalLight::DirectionalLight(const glm::vec3& position)
    : Light(position)
{}

PointLight::PointLight(const glm::vec3& position)
    : Light(position)
{}

auto Light::getPosition() const -> glm::vec3
{
    return this->_position;
}

void Light::setPosition(const glm::vec3& position)
{
    this->_environmentPosition = position;
}

void PointLight::update(const glm::mat4& viewMatrix)
{
    glm::mat4 LightMatrix = glm::translate(viewMatrix, this->_environmentPosition);
    this->_position       = glm::vec3((LightMatrix)*glm::vec4(0, 0, 0, 1));
}

void DirectionalLight::update(const glm::mat4& viewMatrix)
{
    this->_position = glm::vec3((viewMatrix)*glm::vec4(this->_environmentPosition, 0.f));
}