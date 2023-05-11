#pragma once
#include "Material.hpp"

class FacesGroup{
    private : 
        std::string _name;
        std::vector<float> _VertexData  ;
        GLuint _vbo;
        GLuint _vao;

        void createVAO();
    public :
        void createVBO();

        FacesGroup(std::string name);
        FacesGroup();
        ~FacesGroup();

        int getVertextCount() const; 
        std::string getName() const; 
        GLuint getVAO() const; 
        GLuint getVBO() const; 
        std::vector<float> getVertextData() const; 

        void setVertexData(int vIdx, int tIdx, int nIdx, std::vector<CordPosition>& vertices, std::vector<CordTexture>& textures, std::vector<CordNormal>& normals); 
       
    };

    
