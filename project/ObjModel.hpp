#pragma once

#include <cstdlib>
#include <vector>
#include <map>
#include <string>

#include "p6/p6.h"
#include "Material.hpp"


class ObjModel {

    private : 
        struct Position {float x, y, z ;} ; 
        struct Normal {float x, y, z ;} ;
        struct Texture {float x, y, z ;} ;
        
        std::map<std::string, Material> _MaterialMap;   
        std::vector<float> _VertexData  ;  

        void LoadMaterialFile(const std::string name); 
        bool StartWith(std::string line, const char* text); 
        void AddVertexData(int vIdx, int tIdx, int nIdx,  
            std::vector<Position>& vertices, std::vector<Texture>& textures, std::vector<Normal>& normals);

    public : 
        ObjModel();
        ~ObjModel();

        void LoadFromFile(const std::string name); 
        std::vector<float> getVertextData() const; 
        int getVertextCount() const; 
}; 