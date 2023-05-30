#pragma once

#include <vector>
#include "Object.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class Obstacle : public Object {
private:
    p6::Radius _radius;

public:
    Obstacle(const std::vector<ModelPart>& model, ObjectProgram& program);
    Obstacle(const std::vector<ModelPart>& model, ObjectProgram& program, const glm::vec3& position);

    auto get_radius() const -> float;
};