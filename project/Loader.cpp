#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>

#include "p6/p6.h"
#include "Loader.hpp"
#include "Material.hpp"
#include "FacesGroup.hpp"


Loader::Loader(){}

Loader::~Loader(){}

std::vector<FacesGroup> Loader::LoadFromFile(const std::string name, std::map<std::string, Material>& materialMap)
{
    std::vector<Position> vertices; 
    std::vector<Normal> normals; 
    std::vector<Texture> textures; 
    std::vector<FacesGroup> objPart;
    int currentGroup=-1 ; 

    std::ifstream file(name); 
    if (file) {
        std::cout << "object : " << name << "\n" ;
        char currentmtlName[100]; 
        // FacesGroup currentGroup;
        std::string line ; 
        while (std::getline(file, line)){
            if (StartWith(line, "mtllib")){
                char mtlFileName[100]; 
                (void)sscanf(line.c_str(), "mtllib %s", mtlFileName);
                LoadMaterialFile(mtlFileName, materialMap); 
            }
            if (StartWith(line, "v ")){
                Position pos ; 
                sscanf(line.c_str(), "v %f %f %f", &pos.x, &pos.y, &pos.z);
                vertices.push_back(pos); 
            }
            if (StartWith(line, "vn ")){
                Normal n ; 
                sscanf(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
                normals.push_back(n); 
            }
            if (StartWith(line, "vt ")){
                Texture t ; 
                sscanf(line.c_str(), "vt %f %f %f", &t.x, &t.y, &t.z);
                textures.push_back(t); 
            }
            if (StartWith(line, "usemtl")){
                (void)sscanf(line.c_str(), "usemtl %s", currentmtlName);
                objPart.push_back(FacesGroup(currentmtlName));
                currentGroup++ ; 
                // std::cout << "\n\n new currentGroup : " << currentGroup.getName() << "\n";
            }
            if (StartWith(line, "f ")){
                int v1, n1, t1, v2, n2, t2, n3, v3, t3; 
                (void)sscanf(line.c_str(), "f %d/%d/%d %d/%d/ %d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                // std::cout << "f : " << v1 << " " << t1 << " " << n1 << " " << v2 << " " << t2 << " " << n3 << " " << v3 << " " << t3 << " " << n3 <<  "\n" ;
                
                objPart[currentGroup].setVertexData(v1, t1, n1, vertices, textures, normals); 
                objPart[currentGroup].setVertexData(v2, t2, n2, vertices, textures, normals); 
                objPart[currentGroup].setVertexData(v3, t3, n3, vertices, textures, normals); 
            }
        }
        for (int i=0; i<=currentGroup; i++){
            objPart[i].createVBO();
        }
        return objPart ; 
    }
    else {
        std::cerr  << "obj file loading failed \n";
        return objPart; 
    }
}


void Loader::LoadMaterialFile(const std::string name, std::map<std::string, Material>& materialMap)
{
    std::ifstream file(name); 

    std::cout << "material : " << name << "\n" ;
    if (file){
        std::string line; 
        while (std::getline(file, line)){
            char mtlName[100]; 
            if (StartWith(line, "newmtl")){
                (void)sscanf(line.c_str(), "newmtl %s", mtlName);
                if (materialMap.find(mtlName) == materialMap.end()){
                    std::string st = std::string(mtlName);
                    materialMap[st] = Material(); 
                }
            }
            if (StartWith(line, "Kd")){
                Material& material = materialMap[std::string(mtlName)]; 
                sscanf(line.c_str(), "Kd %f %f %f", &material.Kd.x, &material.Kd.y, &material.Kd.z);
            }
            if (StartWith(line, "Ns")){
                Material& material = materialMap[std::string(mtlName)]; 
                sscanf(line.c_str(), "Ns %f", &material.shininess);
            }
            if (StartWith(line, "Ka")){
                Material& material = materialMap[std::string(mtlName)]; 
                sscanf(line.c_str(), "Ka %f %f %f", &material.Ka.x, &material.Ka.y, &material.Ka.z);
            }
            if (StartWith(line, "Ks")){
                Material& material = materialMap[std::string(mtlName)]; 
                sscanf(line.c_str(), "Ks %f %f %f", &material.Ks.x, &material.Ks.y, &material.Ks.z);
            }
            if (StartWith(line, "map_Kd")){
                Material& material = materialMap[std::string(mtlName)]; 
                char path[100]; 
                sscanf(line.c_str(), "map_Kd %s", path);
                material.path = path ; 
            }
        }
    }
    else std::cerr << "Material file loading failed \n" ; 
}

bool Loader::StartWith(std::string line, const char* text)
{
    size_t textLen = strlen(text); 
    if (line.size() < textLen) return false ; 
    for (size_t i=0 ; i<textLen ; i++){
        if(line[i]!=text[i]) return false ; 
    }
    return true ; 
}
