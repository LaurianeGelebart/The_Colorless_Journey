#include "Content.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    
Content::Content()
{}

Content::Content(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program)
:Object(model, lodModel, program) 
{
    this->_position = glm::vec3(0.f); 
    this->_scale = 0.1 ; 
}
