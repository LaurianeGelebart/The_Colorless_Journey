#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>

#include "p6/p6.h"
#include "ObjModel.hpp"


ObjModel::ObjModel(){

}
ObjModel::~ObjModel(){

}

void ObjModel::LoadFromFile(const std::string name)
{
    std::vector<Position> vertices; 
    std::vector<Normal> normals; 

    std::ifstream file(name); 
    if (file) {
        char currentmtlName[100]; 
        std::string line ; 
        while (std::getline(file, line)){
        std::cout << "line : " <<line << "\n" ;
            if (StartWith(line, "mtllib")){
                char mtlFileName[100]; 
                (void)sscanf(line.c_str(), "mtllib %s", mtlFileName);
                // snprintf(mtlFileName, sizeof(mtlFileName), "%s", line.substr(7).c_str());
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
            if (StartWith(line, "usemtl")){
                (void)sscanf(line.c_str(), "mtlLib %s", currentmtlName);
                // snprintf(currentmtlName, sizeof(currentmtlName), "%s", line.substr(7).c_str());
            }
            if (StartWith(line, "f ")){
                int v1, v2 ; 
                int n1, n2 ; 
                int n3, v3 ; 
                // (void)sscanf(line.c_str(), "f %d %d %d %d", &v1, &n1, &v2, &n2);
                (void)sscanf(line.c_str(), "f %d/ /%d %d/ /%d%d/ /%d", &v1, &n1, &v2, &n2, &v3, &n3);

                AddVertexData(v1, n1, currentmtlName, vertices, normals); 
                AddVertexData(v2, n2, currentmtlName, vertices, normals); 
                AddVertexData(v3, n3, currentmtlName, vertices, normals); 
            }
        }
    }
    else {
        std::cerr  << "obj file loading failed \n";
    }
}

std::vector<float> ObjModel::getVertextData()
{
    return this->_VertexData ; 
}

int ObjModel::getVertextCount()
{
    return this->_VertexData.size() / 9; 
} 


void ObjModel::LoadMaterialFile(const std::string name)
{
    std::ifstream file(name); 
    if (file){
        std::string line; 
        while (std::getline(file, line)){
            char mtlName[100]; 
            if (StartWith(line, "newmt1")){
                (void)sscanf(line.c_str(), "newmt1 %s", mtlName);
                // (void)sscanf(line.c_str(), "newmt1 %s", mtlName, sizeof(mtlName));
                this->_MaterialMap[mtlName] = Color(); 
            }
            if (StartWith(line, "Kd")){
                Color& color = this->_MaterialMap[mtlName]; 
                sscanf(line.c_str(), "Kd %f %f %f", &color.r, &color.g, &color.b);
            }
        }
    }
    else std::cerr  <<"Material file loading failed \n" ; 
}

bool ObjModel::StartWith(std::string line, const char* text)
{
    size_t textLen = strlen(text); 
        // std::cout << line[i] << "\n"; 

    if (line.size() < textLen) return false ; 
    for (size_t i=0 ; i<textLen ; i++){
        std::cout << line[i] <<"  " << text[i]<< "\n"; 
        if(line[i]!=text[i]) return false ; 
    }
    return true ; 
}

void ObjModel::AddVertexData(int vIdx, int nIdx, const char* mtl, 
                    std::vector<Position>& vertices, std::vector<Normal>& normals)
{

    // if (vIdx < 1 || vIdx > vertices.size()) {
    //      std::cerr << "Index de position invalide !" << std::endl;
    //     return;
    // }

    // if (nIdx < 1 || nIdx > normals.size()) { 
    //     std::cerr << "Index de normale invalide !" << std::endl;
    //     return;
    // }

    
    Color c = this->_MaterialMap[mtl]; 
    std::cout << vIdx << " "<< nIdx << "\n";

    Position p = vertices[vIdx-1]; 
    std::cout << "tab vertices : " << vertices[vIdx-1].x << "\n";

    Normal n = normals[nIdx-1]; 
    std::cout << "tab normals : " << normals[nIdx-1].x << "\n";


   this->_VertexData.push_back(p.x); 
   this->_VertexData.push_back(p.y); 
   this->_VertexData.push_back(p.z); 
   this->_VertexData.push_back(c.r); 
   this->_VertexData.push_back(c.g); 
   this->_VertexData.push_back(c.b); 
   this->_VertexData.push_back(n.x); 
   this->_VertexData.push_back(n.y); 
   this->_VertexData.push_back(n.z); 
}