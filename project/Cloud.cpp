#include "Cloud.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Cloud::Cloud(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
:Object(facesGroup, program) 
{
    this->_position = Vec(glm::ballRand(15.0)); 
    this->_position.y = p6::random::number(0.4, 0.5) ; 
    this->_scale = p6::random::number(0.05, 0.2) ; 
    this->_velocity = p6::random::number(5, 10) ; 
}

Cloud::Cloud
(std::vector<FacesGroup> facesGroup, ObjectProgram& program, Vec position)
:Object(facesGroup, program)
{
    this->_position = position; 
    this->_position.y = 0.0; 
    this->_scale = p6::random::number(0.05, 0.2) ; 
    this->_velocity = p6::random::number(5, 10) ; 
}


void Cloud::update_position(p6::Context& ctx)
{
    this->_position.x = sin(ctx.time()/8.0)*this->_velocity ; 
    this->_position.z = sin(ctx.time()/5.0) ; 
}