#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"
#include "TrackballCamera.hpp"
#include "FreeflyCamera.hpp"

using Vec = glm::vec3 ; 

class Arpenteur : public Object 
{ 
    private :  
        
    public : 
        // Arpenteur();
        Arpenteur(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        
        // void init(std::vector<FacesGroup> facesGroup, ObjectProgram& program);
        void update_position(const TrackballCamera &ViewMatrix); 

}; 