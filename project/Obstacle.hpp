#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjModel.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

using Vec = glm::vec3 ; 

class Obstacle : public Object 
{ 
    private : 
        // Vec _position ; 
        float _radius ; 
        
    public : 
        Obstacle(const ObjModel& model, const ObjectProgram& program); 

        float get_radius() const; 
}; 