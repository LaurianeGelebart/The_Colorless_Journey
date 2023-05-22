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
    this->_position = glm::vec3(0.f); 
    this->_scale = 0.1 ; 
}
 

void Wanderer::update_position(const TrackballCamera& viewMatrix)
{
    this->_angleY = -viewMatrix.getAngleY();
    this->_position = viewMatrix.getPosition();
}

