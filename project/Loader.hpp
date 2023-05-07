#pragma once

#include <cstdlib>
#include <vector>
#include <map>
#include <string>

#include "p6/p6.h"
#include "Material.hpp"
#include "FacesGroup.hpp"


class Loader {

    private : 

        void LoadMaterialFile(const std::string name, std::map<std::string, Material>& materialMap); 
        bool StartWith(std::string line, const char* text); 
        void AddVertexData(int vIdx, int tIdx, int nIdx,  
            std::vector<Position>& vertices, std::vector<Texture>& textures, std::vector<Normal>& normals);

    public : 
        Loader();
        ~Loader();

        std::vector<FacesGroup> LoadFromFile(const std::string name, std::map<std::string, Material>& materialMap); 
        

}; 