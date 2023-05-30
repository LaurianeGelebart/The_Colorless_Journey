#pragma once

#include <vector>
#include "Object.hpp"
#include "programs/ObjectProgram.hpp"

class Content : public Object {
private:
public:
    Content(const std::vector<ModelPart>& model, ObjectProgram& program);
    Content();
};