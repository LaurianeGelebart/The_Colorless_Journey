#include "IHM.hpp"

IHM::IHM()
= default;

void IHM::draw()
{
    ImGui::Begin("Set params");

    float f = this->_detectionRadius.value * 100;
    ImGui::SliderFloat("Detection radius", &f, 0.0f, 10.0f);
    this->_detectionRadius = f / 100;

    float f2 = this->_collisionRadius.value * 200;
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

auto IHM::getMatchingFactor() const -> float
{
    return this->_matchingFactor;
}

auto IHM::getAvoidFactor() const -> float
{
    return this->_avoidFactor;
}

auto IHM::getCenteringFactor() const -> float
{
    return this->_centeringFactor;
}

auto IHM::getTurnFactor() const -> float
{
    return this->_turnFactor;
}

auto IHM::getCollisionRadius() const -> float
{
    return this->_collisionRadius.value;
}

auto IHM::getDetectionRadius() const -> float
{
    return this->_detectionRadius.value;
}

auto IHM::getSpeed() const -> float
{
    return this->_speed;
}

auto IHM::getBoidsArea() const -> float
{
    return this->_boidsArea;
}

auto IHM::getNbObstacles() const -> int
{
    return this->_nbObstacles;
}

auto IHM::getNbBoids() const -> int
{
    return this->_nbBoids;
}
