#pragma once

#include <cstdlib>
#include <map>
#include "ModelPart.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class Object {
private:
protected:
    ObjectProgram*          _program;
    std::vector<ModelPart> _model;
    glm::vec3               _position;
    float                   _scale  = 0.1;
    float                   _angleY = 0.f;

    Object(std::vector<ModelPart> model, ObjectProgram& program);

public:
    Object();

    void deleteVAO_VBO();

    glm::vec3                getPosition() const;
    float                    getAngleY() const;
    float                    getScale() const;
    std::vector<ModelPart>& getModel();
    void                     draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color);
};