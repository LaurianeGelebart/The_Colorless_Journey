#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"
#include "FreeflyCamera.hpp"

using Vec = glm::vec3 ; 

class Arpenteur : public Object 
{ 
    private :  
        
    public : 
        Arpenteur(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        Arpenteur(std::vector<FacesGroup> facesGroup, ObjectProgram& program, Vec position);

        void update_position(const FreeflyCamera &ViewMatrix); 
}; 