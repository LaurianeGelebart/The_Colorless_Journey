#pragma once

#include <cstdlib>
#include <vector>
#include "Object.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class Content : public Object {
private:
public:
    Content(std::vector<ModelPart> model, ObjectProgram& program);
    Content();
};