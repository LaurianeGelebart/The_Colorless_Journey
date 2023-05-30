#pragma once

#include <map>
#include <vector>
#include "ModelPart.hpp"
#include "programs/ObjectProgram.hpp"

class Object {
private:
protected:
    ObjectProgram*         _program;
    std::vector<ModelPart> _model;
    glm::vec3              _position;
    float                  _scale  = 0.1;
    float                  _angleY = 0.f;

    Object(const std::vector<ModelPart>& model, ObjectProgram& program);

public:
    Object();
    virtual ~Object()                        = default;
    Object(const Object&)                    = default;
    Object(Object&&)                         = delete;
    auto operator=(const Object&) -> Object& = default;
    auto operator=(Object&&) -> Object&      = delete;

    auto getPosition() const -> glm::vec3;
    auto getAngleY() const -> float;
    auto getScale() const -> float;
    auto getModel() -> std::vector<ModelPart>&;

    void draw(const glm::mat4& ViewMatrix, int windowWidth, int windowHeight, std::map<std::string, Material>& materialMap, int color);
    void deleteVAO_VBO();
};