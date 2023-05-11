#include "Content.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Content::Content(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
:Object(facesGroup, program) 
{
    this->_position = Vec(0); 
    // this->_position.y = -0.2;  
    this->_scale = 0.1 ; 
}

Content::Content(std::vector<FacesGroup> facesGroup, ObjectProgram& program, Vec position)
:Object(facesGroup, program)
{
    this->_position = position; 
    this->_position.y = -0.2; 
    this->_scale = 0.1 ; 
}
