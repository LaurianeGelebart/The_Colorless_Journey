#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "ObjectProgram.hpp"
#include "Object.hpp"

class Content : public Object 
{ 
    private : 
        
    public : 
        Content(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program);
        Content();

}; 