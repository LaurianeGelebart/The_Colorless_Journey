#pragma once

#include "p6/p6.h"

class IHM {
private:
    float _matchingFactor  = 0.03;
    float _avoidFactor     = 0.005;
    float _centeringFactor = 0.0005;

    p6::Radius _collisionRadius = 0.015;
    p6::Radius _detectionRadius = 0.025;
    float      _turnFactor      = 0.00006;
    float      _speed           = 0.0015;
    float      _boidsArea       = 0.2;
    int        _nbObstacles     = 60;
    int        _nbBoids         = 50;

public:
    IHM();
    void draw();

    auto getTurnFactor() const -> float;
    auto getMatchingFactor() const -> float;
    auto getAvoidFactor() const -> float;
    auto getCenteringFactor() const -> float;
    auto getCollisionRadius() const -> float;
    auto getDetectionRadius() const -> float;
    auto getSpeed() const -> float;
    auto getBoidsArea() const -> float;
    auto getNbObstacles() const -> int;
    auto getNbBoids() const -> int;
};