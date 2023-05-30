#pragma once

#include <vector>
#include "ModelPart.hpp"
#include "TrackballCamera.hpp"
#include "programs/PanelProgram.hpp"

class PanelInfo {
private:
    PanelProgram*          _panelProgram;
    std::vector<ModelPart> _model;
    glm::vec3              _position;
    float                  _angleX = 0.0f;
    float                  _angleY = 0.f;
    float                  _scale  = 0.1;

    bool _isDisplay       = false;
    bool _hasBeenDislayed = false;

public:
    PanelInfo(const std::vector<ModelPart>& model, PanelProgram& program);
    PanelInfo();

    void appears(const TrackballCamera& viewMatrix);
    void disapears();

    auto getDisplay() const -> bool;
    auto getHasBeenDislayed() const -> bool;
    void draw(const glm::mat4& ViewMatrix, int windowWidth, int windowHeight, std::map<std::string, Material>& materialMap, int color);
    void deleteVAO_VBO();
};