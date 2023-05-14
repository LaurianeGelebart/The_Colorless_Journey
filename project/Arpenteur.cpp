#include "Arpenteur.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

// Arpenteur::Arpenteur()
// {
//     this->_position = Vec(0.f); 
//     this->_scale = 1 ; 
// }

Arpenteur::Arpenteur(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
:Object(facesGroup, program) 
{
    this->_position = Vec(0.f); 
    this->_scale = 0.1 ; 
}

// void Arpenteur::init(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
// {
//     this->_facesGroup = facesGroup;
//     this->_program = program;
// }


void Arpenteur::update_position(const FreeflyCamera &ViewMatrix)
{
    // Vec cameraPosition = ViewMatrix.getPosition() ; 
    // Vec cameraDirection = -ViewMatrix.getFront();
    // Vec objectPosition = cameraPosition + cameraDirection * 2.0f; // multiplier par une distance de 2.0f

    // this->_position = objectPosition;
}