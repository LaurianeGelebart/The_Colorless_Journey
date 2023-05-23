#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"
#include "Object.hpp"
#include "TrackballCamera.hpp"


class Wanderer : public Object 
{ 
    private :  

    public : 
        Wanderer();
        Wanderer(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program);

        void update_position(const TrackballCamera& viewMatrix); 
        float getAngle() const ;

}; 