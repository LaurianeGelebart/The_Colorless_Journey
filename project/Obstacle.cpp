#include "Obstacle.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Obstacle::Obstacle(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program)
:Object(model, lodModel, program) 
{
    this->_position = glm::vec3(glm::ballRand(2.0)); 
    this->_position.y = 0.0; 
    this->_radius = p6::random::number(0.1, 0.2) ; 
}

Obstacle::Obstacle(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program, glm::vec3 position)
:Object(model, lodModel, program) 
{
    this->_position = position; 
    this->_position.y = 0.0; 
    this->_radius = p6::random::number(0.1, 0.2) ; 
}


float Obstacle::get_radius() const
{
    return this->_radius ; 
}