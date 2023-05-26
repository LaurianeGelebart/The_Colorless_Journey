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
        Wanderer(std::vector<FacesGroup> model, ObjectProgram& program);

        void updatePosition(const TrackballCamera& viewMatrix, p6::Context& ctx); 
        float getAngle() const ;

}; 