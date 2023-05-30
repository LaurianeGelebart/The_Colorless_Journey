#pragma once
#include "Material.hpp"

class ModelPart {
private:
    std::string        _name;
    std::vector<float> _VertexData;
    std::vector<int>   _VertexIndices;
    GLuint             _vbo;
    GLuint             _vao;
    GLuint             _ibo;

    void createVAO();
    void createVBO();
    void createIBO();

public:
    ModelPart(std::string name);
    ModelPart();
    ~ModelPart();

    void createVBO_IBO_VAO();

    int                getVertextCount() const;
    std::string        getName() const;
    GLuint             getVAO() const;
    GLuint             getVBO() const;
    GLuint             getIBO() const;
    std::vector<float> getVertextData() const;

    void setVertexData(int vIdx, int tIdx, int nIdx, std::vector<CordPosition>& vertices, std::vector<CordTexture>& textures, std::vector<CordNormal>& normals);
};
