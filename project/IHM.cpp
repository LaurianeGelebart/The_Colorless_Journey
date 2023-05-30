#include "IHM.hpp"
#include <iostream>

IHM::IHM()
{}

void IHM::draw()
{
    ImGui::Begin("Set params");

    float f = this->_detectionRadius * 100;
    ImGui::SliderFloat("Detection radius", &f, 0.0f, 10.0f);
    this->_detectionRadius = f / 100;

    float f2 = this->_collisionRadius * 200;
    ImGui::SliderFloat("Collision radius", &f2, 0.0f, 10.0f);
    this->_collisionRadius = f2 / 200;

    float f3 = this->_turnFactor * 100000;
    ImGui::SliderFloat("Boids turn factor", &f3, 1.0f, 10.0f);
    this->_turnFactor = f3 / 100000;

    float f4 = this->_speed * 20000;
    ImGui::SliderFloat("Max boids speed", &f4, 1.0f, 100.0f);
    this->_speed = f4 / 20000;

    float f5 = this->_boidsArea * 10;
    ImGui::SliderFloat("Boids area size", &f5, 1.0f, 10.0f);
    this->_boidsArea = f5 / 10;

    int i1 = this->_nbBoids;
    ImGui::SliderInt("Boids", &i1, 0, 200);
    this->_nbBoids = i1;

    int i2 = this->_nbObstacles;
    ImGui::SliderInt("Objects in the scene", &i2, 10, 100);
    this->_nbObstacles = i2;

    ImGui::End();
}

float IHM::getMatchingFactor() const
{
    return this->_matchingFactor;
}

float IHM::getAvoidFactor() const
{
    return this->_avoidFactor;
}

float IHM::getCenteringFactor() const
{
    return this->_centeringFactor;
}

float IHM::getTurnFactor() const
{
    return this->_turnFactor;
}

float IHM::getCollisionRadius() const
{
    return this->_collisionRadius;
}

float IHM::getDetectionRadius() const
{
    return this->_detectionRadius;
}

float IHM::getSpeed() const
{
    return this->_speed;
}

float IHM::getBoidsArea() const
{
    return this->_boidsArea;
}

int IHM::getNbObstacles() const
{
    return this->_nbObstacles;
}

int IHM::getNbBoids() const
{
    return this->_nbBoids;
}
