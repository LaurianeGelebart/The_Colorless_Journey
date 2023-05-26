#include "Content.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    
Content::Content()
{}

Content::Content(std::vector<FacesGroup> model, ObjectProgram& program)
:Object(model, program) 
{
    this->_position = glm::vec3(0.f); 
    this->_scale = 0.1 ; 
}
