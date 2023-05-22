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
        Obstacle(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program);
        Obstacle(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program, Vec position);

        float get_radius() const; 
}; 