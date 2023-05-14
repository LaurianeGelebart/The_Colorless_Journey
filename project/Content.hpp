#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"

using Vec = glm::vec3 ; 

class Content : public Object 
{ 
    private : 
        
    public : 
        Content(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        // Content();

        // void init(std::vector<FacesGroup> facesGroup, ObjectProgram& program);

}; 