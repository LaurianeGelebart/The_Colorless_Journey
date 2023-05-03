#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>

#include "p6/p6.h"
#include "ObjModel.hpp"
#include "Material.hpp"


ObjModel::ObjModel(){

}
ObjModel::~ObjModel(){

}

void ObjModel::LoadFromFile(const std::string name, const std::vector<Material>& Material)
{
    std::vector<Position> vertices; 
    std::vector<Normal> normals; 
    std::vector<Texture> textures; 

    std::ifstream file(name); 
    if (file) {
        std::cout << "name : " << name << "\n" ;
        char currentmtlName[100]; 
        std::string line ; 
        while (std::getline(file, line)){
            if (StartWith(line, "mtllib")){
                char mtlFileName[100]; 
                (void)sscanf(line.c_str(), "mtllib %s", mtlFileName);
                LoadMaterialFile(mtlFileName); 
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
                (void)sscanf(line.c_str(), "mtlLib %s", currentmtlName);
            }
            if (StartWith(line, "f ")){
                int v1, n1, t1, v2, n2, t2, n3, v3, t3; 
                (void)sscanf(line.c_str(), "f %d/%d/%d %d/%d/ %d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);

                // std::cout << "f : " << v1 << " " << t1 << " " << n1 << " " << v2 << " " << t2 << " " << n3 << " " << v3 << " " << t3 << " " << n3 <<  "\n" ;
                
                AddVertexData(v1, t1, n1, vertices, textures, normals); 
                AddVertexData(v2, t2, n2, vertices, textures, normals); 
                AddVertexData(v3, t3, n3, vertices, textures, normals); 
            }
        }
    }
    else {
        std::cerr  << "obj file loading failed \n";
    }
}


void ObjModel::LoadMaterialFile(const std::string name)
{
    std::ifstream file(name); 

    std::cout << "material : " << name << "\n" ;
    if (file){
        std::string line; 
        while (std::getline(file, line)){
            char mtlName[100]; 
            if (StartWith(line, "newmt1")){
                (void)sscanf(line.c_str(), "newmt1 %s", mtlName);
                this->_MaterialMap[mtlName] = Material(); 
            }
            // if (StartWith(line, "Kd")){
            //     Color& color = this->_MaterialMap[mtlName]; 
            //     sscanf(line.c_str(), "Kd %f %f %f", &color.r, &color.g, &color.b);
            // }
            if (StartWith(line, "Ns")){
                Material& material = this->_MaterialMap[mtlName]; 
                sscanf(line.c_str(), "Ns %f", &material.shininess);
            }
            if (StartWith(line, "Ka")){
                Material& material = this->_MaterialMap[mtlName]; 
                sscanf(line.c_str(), "Ka %f %f %f", &material.Ka.x, &material.Ka.y, &material.Ka.z);
            }
            if (StartWith(line, "Ks")){
                Material& material = this->_MaterialMap[mtlName]; 
                sscanf(line.c_str(), "Ks %f %f %f", &material.Ks.x, &material.Ks.y, &material.Ks.z);
            }
            if (StartWith(line, "map_Kd")){
                Material& material = this->_MaterialMap[mtlName]; 
                char name[100]; 
                sscanf(line.c_str(), "map_Kd %s", name);
                material.name = name ; 
            }
        }
    }
    else std::cerr << "Material file loading failed \n" ; 
}

std::vector<float> ObjModel::getVertextData() const
{
    return this->_VertexData ; 
}

int ObjModel::getVertextCount() const
{
    return this->_VertexData.size() / 9; 
} 



bool ObjModel::StartWith(std::string line, const char* text)
{
    size_t textLen = strlen(text); 
    if (line.size() < textLen) return false ; 
    for (size_t i=0 ; i<textLen ; i++){
        if(line[i]!=text[i]) return false ; 
    }
    return true ; 
}

void ObjModel::AddVertexData(int vIdx, int tIdx, int nIdx,
    std::vector<Position>& vertices, std::vector<Texture>& textures, std::vector<Normal>& normals)
{

    // if (vIdx < 1 || vIdx > vertices.size()) {
    //      std::cerr << "Index de position invalide !" << std::endl;
    //     return;
    // }

    // if (nIdx < 1 || nIdx > normals.size()) { 
    //     std::cerr << "Index de normale invalide !" << std::endl;
    //     return;
    // }

    Position p = vertices[vIdx-1]; 
    // std::cout << "tab vertices : " << vertices[vIdx-1].x << "\n";

    Texture t = textures[tIdx-1]; 
    // std::cout << "tab textures : " << textures[tIdx-1].x << "\n";

    Normal n = normals[nIdx-1]; 
    // std::cout << "tab normals : " << normals[nIdx-1].x << "\n\n";


   this->_VertexData.push_back(p.x); 
   this->_VertexData.push_back(p.y); 
   this->_VertexData.push_back(p.z); 
   this->_VertexData.push_back(t.x); 
   this->_VertexData.push_back(t.y); 
   this->_VertexData.push_back(t.z); 
   this->_VertexData.push_back(n.x); 
   this->_VertexData.push_back(n.y); 
   this->_VertexData.push_back(n.z); 
}
