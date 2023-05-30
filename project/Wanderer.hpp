#pragma once

#include <cstdlib>
#include <vector>
#include "Object.hpp"
#include "TrackballCamera.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class Wanderer : public Object {
private:
public:
    Wanderer();
    Wanderer(std::vector<ModelPart> model, ObjectProgram& program);

    void  updatePosition(const TrackballCamera& viewMatrix, p6::Context& ctx);
    float getAngle() const;
};