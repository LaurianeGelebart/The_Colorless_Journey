#pragma once

#include <cstdlib>
#include <vector>
#include <map>
#include <string>

#include "p6/p6.h"


class ObjModel {

    private : 
        struct Position {float x, y, z ;} ; 
        struct Color {float r, g, b ; } ; 
        struct Normal {float x, y, z ;} ;

        std::map<std::string, Color> _MaterialMap;  
        std::vector<float> _VertexData  ;  

        void LoadMaterialFile(const std::string name); 
        bool StartWith(std::string line, const char* text); 
        void AddVertexData(int vIdx, int nIdx, const char* mtl, 
                    std::vector<Position>& vertices, std::vector<Normal>& normals); 
        
    public : 
        ObjModel();
        ~ObjModel();

        void LoadFromFile(const std::string name); 
        std::vector<float> getVertextData(); 
        int getVertextCount(); 

}; 