#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"

class Cloud : public Object 
{ 
    private : 
        float _velocity; 
        
    public : 
        Cloud(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program);
        Cloud(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program, glm::vec3 position);

        void update_position(p6::Context& ctx); 
}; 