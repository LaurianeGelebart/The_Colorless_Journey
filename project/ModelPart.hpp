#pragma once
#include <vector>
#include "Material.hpp"

class ModelPart {
private:
    std::string        _name;
    std::vector<float> _vertexData;
    std::vector<int>   _vertexIndices;
    GLuint             _vbo;
    GLuint             _vao;
    GLuint             _ibo;

    void createVAO();
    void createVBO();
    void createIBO();

public:
    explicit ModelPart(const std::string& name);
    ModelPart();
    ModelPart(const ModelPart&)                    = default;
    ModelPart(ModelPart&&)                         = delete;
    auto operator=(const ModelPart&) -> ModelPart& = default;
    auto operator=(ModelPart&&) -> ModelPart&      = delete;
    ~ModelPart();

    void createVBO_IBO_VAO();

    auto getVertextCount() const -> int;
    auto getName() const -> std::string;
    auto getVAO() const -> GLuint;
    auto getVBO() const -> GLuint;
    auto getIBO() const -> GLuint;
    auto getVertextData() const -> std::vector<float>;

    void setVertexData(int vIdx, int tIdx, int nIdx, const std::vector<CordPosition>& vertices, const std::vector<CordTexture>& textures, const std::vector<CordNormal>& normals);
};
