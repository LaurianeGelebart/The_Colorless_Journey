#include "Obstacle.hpp"
#include "ObjModel.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Obstacle::Obstacle(const ObjModel& model, const ObjectProgram& program)
:Object(model, program) 
{
    this->_position = Vec(glm::ballRand(7.0)); 
    this->_radius = p6::random::number(0.1, 0.2) ; 
}


float Obstacle::get_radius() const
{
    return this->_radius ; 
}