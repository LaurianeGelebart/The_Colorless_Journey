#pragma once

#include <vector>
#include "IHM.hpp"
#include "ModelPart.hpp"
#include "Obstacle.hpp"
#include "p6/p6.h"
#include "programs/ColorProgram.hpp"

class Boid {
private:
    glm::vec3                           _velocity;
    float                               _borne_velocity = 0.001;
    p6::Color                           _color;
    glm::vec3                           _centerPosition;
    ColorProgram*                       _program;
    std::vector<std::vector<ModelPart>> _models;
    glm::vec3                           _position;
    float                               _scale = 0.1;
    int                                 _lod   = 1;

    void collisionBox(const IHM& ihm);
    void collisionBords(const IHM& ihm);
    void bounce(const glm::vec3& obstaclePosition);
    void collisionObstacles(const std::vector<Obstacle>& obstacles, const IHM& ihm);
    void collisionBoids(const std::vector<Boid>& boids, const IHM& ihm);

    void limitSpeed(const IHM& ihm);
    void move(const p6::Context& ctx);

public:
    Boid(const std::vector<ModelPart>& model, const std::vector<ModelPart>& lodModel, ColorProgram& program, glm::vec3 magicPos);

    auto getPosition() const -> glm::vec3;
    auto getVelocity() const -> glm::vec3;

    void updatePosition();
    void collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, const IHM& ihm);
    void draw(const glm::mat4& ViewMatrix, int windowWidth, int windowHeight, std::map<std::string, Material>& materialMap);

    void checkLOD(const glm::vec3& fireflyPosition);
    void deleteVAO_VBO();
};