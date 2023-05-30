#include "ModelPart.hpp"

ModelPart::ModelPart(const std::string& name)
    : _name(name) {}

ModelPart::ModelPart() = default;

ModelPart::~ModelPart() {}

auto ModelPart::getVertextData() const -> std::vector<float>
{
    return this->_vertexData;
}

auto ModelPart::getVertextCount() const -> int
{
    return this->_vertexData.size() / 8;
}

auto ModelPart::getName() const -> std::string
{
    return this->_name;
}

auto ModelPart::getVAO() const -> GLuint
{
    return this->_vao;
}

auto ModelPart::getVBO() const -> GLuint
{
    return this->_vbo;
}

auto ModelPart::getIBO() const -> GLuint
{
    return this->_ibo;
}

void ModelPart::setVertexData(int vIdx, int tIdx, int nIdx, const std::vector<CordPosition>& vertices, const std::vector<CordTexture>& textures, const std::vector<CordNormal>& normals)
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

    CordTexture t = textures[tIdx - 1];

    CordNormal n = normals[nIdx - 1];

    this->_vertexData.push_back(p.x);
    this->_vertexData.push_back(p.y);
    this->_vertexData.push_back(p.z);
    this->_vertexData.push_back(t.x);
    this->_vertexData.push_back(t.y);
    this->_vertexData.push_back(n.x);
    this->_vertexData.push_back(n.y);
    this->_vertexData.push_back(n.z);

    this->_vertexIndices.push_back(vIdx);
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

    std::vector<float> vertices = this->_vertexData;

    glBufferData(GL_ARRAY_BUFFER, this->_vertexData.size() * sizeof(GLfloat), this->_vertexData.data(), GL_STATIC_DRAW);
}

void ModelPart::createIBO()
{
    glGenBuffers(1, &(this->_ibo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_vertexIndices.size() * sizeof(int), this->_vertexIndices.data(), GL_STATIC_DRAW);
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

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
