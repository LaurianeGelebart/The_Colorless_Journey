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


void Arpenteur::update_position(const TrackballCamera &ViewMatrix)
{
    Vec cameraPosition = ViewMatrix.getPosition() *10.f; 
    this->_angle = -ViewMatrix.getAngleY(); 

    this->_position = cameraPosition;

}
