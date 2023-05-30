#include "Wanderer.hpp"

Wanderer::Wanderer() = default;

Wanderer::Wanderer(const std::vector<ModelPart>& model, ObjectProgram& program)
    : Object(model, program)
{}

void Wanderer::updatePosition(const TrackballCamera& viewMatrix, p6::Context& ctx)
{
    this->_angleY   = -viewMatrix.getAngleY();
    float positionY = viewMatrix.getPosition().y + (sin(ctx.time() * 10.0) * 0.005);
    this->_position = glm::vec3(viewMatrix.getPosition().x, positionY, viewMatrix.getPosition().z);
}

auto Wanderer::getAngle() const -> float
{
    return this->_angleY;
}
