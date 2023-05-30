#pragma once

#include <cstdlib>
#include <vector>
#include "Object.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class Cloud : public Object {
private:
    float _velocity;

public:
    Cloud(std::vector<ModelPart> model, ObjectProgram& program);
    Cloud(std::vector<ModelPart> model, ObjectProgram& program, glm::vec3 position);

    void updatePosition(p6::Context& ctx);
};