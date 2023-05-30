#include "Cloud.hpp"
#include <cmath>
#include "glm/gtc/random.hpp"

Cloud::Cloud(const std::vector<ModelPart>& model, ObjectProgram& program)
    : Object(model, program), _velocity(p6::random::number(1.0, 5.0))
{
    this->_position   = glm::vec3(glm::ballRand(1.5));
    this->_position.y = p6::random::number(0.05, 0.1);
    this->_scale      = p6::random::number(0.05, 0.3);
}

void Cloud::updatePosition(const p6::Context& ctx)
{
    this->_position.x += 0.001f * std::sin(ctx.time() * 0.8f) * this->_velocity;
    this->_position.z += 0.001f * std::sin(ctx.time() * 0.5f) * this->_velocity;

    this->_position.x = glm::clamp(this->_position.x, -1.5f, 1.5f);
    this->_position.z = glm::clamp(this->_position.z, -1.5f, 1.5f);
}