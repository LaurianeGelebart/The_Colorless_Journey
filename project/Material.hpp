#pragma once

#include "Texture.hpp"

using Vec = glm::vec3 ; 

struct Material{
    Vec Ka = Vec(-1.f);
    Vec Ks = Vec(-1.f);
    Vec Kd = Vec(-1.f);
    float shininess = -1.f;  
    std::string path;
    Texture texture;
};


struct CordPosition {float x, y, z ;} ; 
struct CordNormal {float x, y, z ;} ;
struct CordTexture {float x, y, z ;} ;