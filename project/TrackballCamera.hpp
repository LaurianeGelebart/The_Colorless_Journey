#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Obstacle.hpp"

class TrackballCamera {
private:
    float _distance = 0.5;
    float _angleX   = 17.f;
    float _angleY   = 0.f;

    glm::vec3 _position = glm::vec3(0.0, -0.05, -0.8);

public:
    TrackballCamera();

    auto getViewMatrix() const -> glm::mat4;
    auto getPosition() const -> glm::vec3;
    auto getAngleY() const -> float;
    auto getAngleX() const -> float;

    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void moveFront(float delta, const std::vector<Obstacle>& obstacles);
    void moveLeft(float delta, const std::vector<Obstacle>& obstacles);
};
