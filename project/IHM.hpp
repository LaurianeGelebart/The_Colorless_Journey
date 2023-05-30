#pragma once

#include <cstdlib>
#include <vector>
#include "ModelPart.hpp"
#include "p6/p6.h"
#include "programs/ObjectProgram.hpp"

class IHM {
private:
    float _matchingFactor  = 0.03;
    float _avoidFactor     = 0.005;
    float _centeringFactor = 0.0005;

    float _collisionRadius = 0.015;
    float _detectionRadius = 0.025;
    float _turnFactor      = 0.00006;
    float _speed           = 0.0015;
    float _boidsArea       = 0.2;
    int   _nbObstacles     = 60;
    int   _nbBoids         = 50;

public:
    IHM();
    void draw();

    float getTurnFactor() const;
    float getMatchingFactor() const;
    float getAvoidFactor() const;
    float getCenteringFactor() const;
    float getCollisionRadius() const;
    float getDetectionRadius() const;
    float getSpeed() const;
    float getBoidsArea() const;
    int   getNbObstacles() const;
    int   getNbBoids() const;
};