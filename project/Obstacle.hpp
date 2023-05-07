#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"

using Vec = glm::vec3 ; 

class Obstacle : public Object 
{ 
    private : 
        float _radius ; 
        
    public : 
        Obstacle(std::vector<FacesGroup> facesGroup, ObjectProgram& program);

        float get_radius() const; 
}; 