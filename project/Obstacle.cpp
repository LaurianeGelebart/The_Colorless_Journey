#include "Obstacle.hpp"
#include "glm/gtc/random.hpp"

Obstacle::Obstacle(const std::vector<ModelPart>& model, ObjectProgram& program)
    : Object(model, program)
{
    this->_position   = glm::vec3(glm::ballRand(2.0));
    this->_position.y = 0.0;
    this->_radius     = p6::random::number(0.1, 0.2);
}

Obstacle::Obstacle(const std::vector<ModelPart>& model, ObjectProgram& program, const glm::vec3& position)
    : Object(model, program)
{
    this->_position   = position;
    this->_position.y = 0.0;
    this->_radius     = p6::random::number(0.1, 0.2);
}

auto Obstacle::get_radius() const -> float
{
    return this->_radius.value;
}