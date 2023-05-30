#pragma once

#include <vector>
#include "Object.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class Cloud : public Object {
private:
    float _velocity;

public:
    Cloud(const std::vector<ModelPart>& model, ObjectProgram& program);

    void updatePosition(const p6::Context& ctx);
};