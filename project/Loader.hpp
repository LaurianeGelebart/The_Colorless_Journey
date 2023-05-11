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

        void LoadTextures(Material& material);
        void LoadMaterial(const std::string name, std::map<std::string, Material>& materialMap, int& nb_slot); 
        bool StartWith(std::string line, const char* text); 
        void AddVertexData(int vIdx, int tIdx, int nIdx,  
            std::vector<CordPosition>& vertices, std::vector<CordTexture>& textures, std::vector<CordNormal>& normals);

    public : 
        Loader();
        ~Loader();

        std::vector<FacesGroup> LoadFromFile(const std::string name, std::map<std::string, Material>& materialMap, int& nb_slot); 
        
}; 