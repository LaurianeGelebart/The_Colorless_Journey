#pragma once
#include "Material.hpp"

class FacesGroup{
    private : 
        std::string _name;
        std::vector<float> _VertexData  ;
        GLuint _vbo;
        GLuint _vao;

        void createVBO();
        void createVAO();

    public :
        FacesGroup(std::string name);
        FacesGroup();
        ~FacesGroup();

        int getVertextCount() const; 
        std::string getName() const; 
        GLuint getVAO() const; 
        GLuint getVBO() const; 
        std::vector<float> getVertextData() const; 

        void setVertexData(int vIdx, int tIdx, int nIdx, std::vector<Position>& vertices, std::vector<Texture>& textures, std::vector<Normal>& normals); 
       
    };

    
