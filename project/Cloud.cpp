#include "Cloud.hpp"
#include "programs/ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Cloud::Cloud(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program)
:Object(model, lodModel, program) 
{
    this->_position = glm::vec3(glm::ballRand(1.5)); 
    this->_position.y = p6::random::number(0.05, 0.1) ; 
    this->_scale = p6::random::number(0.05, 0.3) ; 
    this->_velocity = p6::random::number(1.0, 5.0) ; 
}


void Cloud::update_position(p6::Context& ctx)
{
    this->_position.x += 0.001*sin(ctx.time()*0.8)*this->_velocity ; 
    this->_position.z += 0.001*sin(ctx.time()*0.5)*this->_velocity ; 
    
    this->_position.x = glm::clamp(this->_position.x, -1.5f, 1.5f);
    this->_position.z = glm::clamp(this->_position.z, -1.5f, 1.5f);

    // std::cout << "cloud " << this->_position.x << " - " << this->_position.y << " - "<< this->_position.z << "\n";
}