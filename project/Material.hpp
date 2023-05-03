#pragma once
using Vec = glm::vec3 ; 

struct Material{
        Vec Ka, Ks ;
        float shininess ; 
        std::string name;
    };