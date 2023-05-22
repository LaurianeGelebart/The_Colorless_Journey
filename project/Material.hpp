#pragma once

#include "Texture.hpp"
#include <vector>

struct Material{
    glm::vec3 Ka = glm::vec3(-1.f);
    glm::vec3 Ks = glm::vec3(-1.f);
    glm::vec3 Kd = glm::vec3(-1.f);
    float shininess = -1.f;  
    std::string path;
    std::vector<Texture> texture;
};


struct CordPosition {float x, y, z ;} ; 
struct CordNormal {float x, y, z ;} ;
struct CordTexture {float x, y ;} ;