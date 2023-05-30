#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include "Loader.hpp"
#include "Material.hpp"
#include "p6/p6.h"

ModelPart::ModelPart(std::string name)
    : _name(name) {}

ModelPart::ModelPart() {}

ModelPart::~ModelPart() {}

std::vector<float> ModelPart::getVertextData() const
{
    return this->_VertexData;
}

int ModelPart::getVertextCount() const
{
    return this->_VertexData.size() / 8;
}

std::string ModelPart::getName() const
{
    return this->_name;
}

GLuint ModelPart::getVAO() const
{
    return this->_vao;
}

GLuint ModelPart::getVBO() const
{
    return this->_vbo;
}

GLuint ModelPart::getIBO() const
{
    return this->_ibo;
}

void ModelPart::setVertexData(int vIdx, int tIdx, int nIdx, std::vector<CordPosition>& vertices, std::vector<CordTexture>& textures, std::vector<CordNormal>& normals)
{
    if (vIdx < 1 || vIdx > vertices.size())
    {
        std::cerr << "Index de position invalide !" << std::endl;
        return;
    }

    if (nIdx < 1 || nIdx > normals.size())
    {
        std::cerr << "Index de normale invalide !" << std::endl;
        return;
    }

    CordPosition p = vertices[vIdx - 1];
    // std::cout << "tab vertices : " << vertices[vIdx-1].x << "\n";

    CordTexture t = textures[tIdx - 1];
    // std::cout << "tab textures : " << textures[tIdx-1].x << "\n";

    CordNormal n = normals[nIdx - 1];
    // std::cout << "tab normals : " << normals[nIdx-1].x << "\n\n";

    this->_VertexData.push_back(p.x);
    this->_VertexData.push_back(p.y);
    this->_VertexData.push_back(p.z);
    this->_VertexData.push_back(t.x);
    this->_VertexData.push_back(t.y);
    this->_VertexData.push_back(n.x);
    this->_VertexData.push_back(n.y);
    this->_VertexData.push_back(n.z);

    this->_VertexIndices.push_back(vIdx);
}

void ModelPart::createVBO_IBO_VAO()
{
    this->createVBO();
    this->createIBO();
    this->createVAO();
}

void ModelPart::createVBO()
{
    glGenBuffers(1, &(this->_vbo));
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

    std::vector<float> vertices = this->_VertexData;

    glBufferData(GL_ARRAY_BUFFER, this->_VertexData.size() * sizeof(GLfloat), &(this->_VertexData[0]), GL_STATIC_DRAW);
}

void ModelPart::createIBO()
{
    glGenBuffers(1, &(this->_ibo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_VertexIndices.size() * sizeof(int), this->_VertexIndices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ModelPart::createVAO()
{
    glGenVertexArrays(1, &(this->_vao));
    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);

    const GLuint VERTEX_ATTR_POSITION  = 0;
    const GLuint VERTEX_ATTR_NORMAL    = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);                           //(const GLvoid*)offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));    //(const GLvoid*)offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //(const GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
