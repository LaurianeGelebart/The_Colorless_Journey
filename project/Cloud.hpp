#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"
#include "Object.hpp"

class Cloud : public Object 
{ 
    private : 
        float _velocity;
        
    public : 
        Cloud(std::vector<FacesGroup> model, ObjectProgram& program);
        Cloud(std::vector<FacesGroup> model, ObjectProgram& program, glm::vec3 position);

        void updatePosition(p6::Context& ctx); 
}; 