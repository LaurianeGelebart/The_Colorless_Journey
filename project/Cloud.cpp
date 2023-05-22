#include "Cloud.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Cloud::Cloud(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program)
:Object(model, lodModel, program) 
{
    this->_position = glm::vec3(glm::ballRand(1.5)); 
    this->_position.y = p6::random::number(0.15, 0.15) ; 
    this->_scale = p6::random::number(5.0, 6.0) ; 
    this->_velocity = p6::random::number(0.5, 1.0) ; 
}


void Cloud::update_position(p6::Context& ctx)
{
    this->_position.x = sin(ctx.time()/0.8)*this->_velocity ; 
    this->_position.z = sin(ctx.time()/0.5) ; 
    // std::cout << "cloud " << this->_position.x << " - " << this->_position.y << " - "<< this->_position.z << "\n";
}