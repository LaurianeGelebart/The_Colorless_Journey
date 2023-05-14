#include "Content.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Content::Content(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
:Object(facesGroup, program) 
{
    this->_position = Vec(0.f); 
    this->_scale = 0.1 ; 
}

// Content::Content()
// {
//     this->_position = Vec(0.f); 
//     this->_scale = 0.1 ; 
// }

// void Content::init(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
// {
//     this->_facesGroup = facesGroup;
//     this->_program = program;
// }
