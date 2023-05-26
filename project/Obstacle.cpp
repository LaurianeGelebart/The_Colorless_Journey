#include <iostream>
#include "glm/gtc/random.hpp"

#include "Obstacle.hpp"
#include "programs/ObjectProgram.hpp"
#include "Object.hpp"
    

Obstacle::Obstacle(std::vector<FacesGroup> model, ObjectProgram& program)
:Object(model, program) 
{
    this->_position = glm::vec3(glm::ballRand(2.0)); 
    this->_position.y = 0.0; 
    this->_radius = p6::random::number(0.1, 0.2) ; 
}

Obstacle::Obstacle(std::vector<FacesGroup> model, ObjectProgram& program, glm::vec3 position)
:Object(model, program) 
{
    this->_position = position; 
    this->_position.y = 0.0; 
    this->_radius = p6::random::number(0.1, 0.2) ; 
}


float Obstacle::get_radius() const
{
    return this->_radius ; 
}