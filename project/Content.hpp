#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"
#include "Object.hpp"

class Content : public Object 
{ 
    private : 
        
    public : 
        Content(std::vector<FacesGroup> model, ObjectProgram& program);
        Content();

}; 