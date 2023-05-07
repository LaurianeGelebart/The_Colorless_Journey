#pragma once
using Vec = glm::vec3 ; 

struct Material{
    Vec Ka, Ks, Kd;
    float shininess ; 
    std::string path;
};


struct Position {float x, y, z ;} ; 
struct Normal {float x, y, z ;} ;
struct Texture {float x, y, z ;} ;