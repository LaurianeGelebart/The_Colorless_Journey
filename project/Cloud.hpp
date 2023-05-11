#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"

using Vec = glm::vec3 ; 

class Cloud : public Object 
{ 
    private : 
        float _velocity; 
        
    public : 
        Cloud(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        Cloud(std::vector<FacesGroup> facesGroup, ObjectProgram& program, Vec position);

        void update_position(p6::Context& ctx); 
}; 