#include <iostream>
#include "glm/gtc/random.hpp"
    
#include "Wanderer.hpp"
#include "programs/ObjectProgram.hpp"
#include "Object.hpp"

Wanderer::Wanderer()
{}

Wanderer::Wanderer(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program)
:Object(model, lodModel, program) 
{
    this->_scale = 0.1 ; 
}
 

void Wanderer::update_position(const TrackballCamera& viewMatrix, p6::Context& ctx)
{
    this->_angleY = -viewMatrix.getAngleY();
    float positionY = viewMatrix.getPosition().y + (sin(ctx.time()*10.0)*0.005) ; 
    this->_position = glm::vec3(viewMatrix.getPosition().x, positionY, viewMatrix.getPosition().z);
}

float Wanderer::getAngle() const 
{
    return this->_angleY; 
}
