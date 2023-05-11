#include "Arpenteur.hpp"
#include "ObjectProgram.hpp"
#include "Object.hpp"

#include <iostream>
#include "glm/gtc/random.hpp"
    

Arpenteur::Arpenteur(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
:Object(facesGroup, program) 
{
    this->_position = Vec(glm::ballRand(15.0)); 
    this->_position.y = p6::random::number(0.4, 0.5) ; 
    this->_scale = 1 ; 
}

Arpenteur::Arpenteur
(std::vector<FacesGroup> facesGroup, ObjectProgram& program, Vec position)
:Object(facesGroup, program)
{
    this->_position = position; 
    this->_position.y = 0.0; 
    this->_scale = 1 ; 
}


void Arpenteur::update_position(const FreeflyCamera &ViewMatrix)
{
    Vec cameraPosition = ViewMatrix.getPosition() ; 
    Vec cameraDirection = -ViewMatrix.getFront();
    Vec objectPosition = cameraPosition + cameraDirection * 2.0f; // multiplier par une distance de 2.0f

    this->_position = objectPosition;
}