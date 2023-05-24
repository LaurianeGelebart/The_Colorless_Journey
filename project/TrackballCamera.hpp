#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "Material.hpp"
#include "Obstacle.hpp"


class TrackballCamera 
{

    private:
        float _distance = 0.5; 
        float _angleX = 17.f; 
        float _angleY = 0.f; 

        glm::vec3 _position = glm::vec3(0.0, -0.05, -0.8);


        bool isCollisionBorder(glm::vec3 position) const;
        bool isCollisionObstacles(glm::vec3 position, std::vector<Obstacle> obstacles) const;
        bool checkMovingPosition(glm::vec3 position, std::vector<Obstacle> obstacles) const;
        bool checkRotatingAngleX(float angle) const;
        bool checkRotatingAngleY(float angle) const;

    public:
        TrackballCamera(); 

        glm::mat4 getViewMatrix() const ;
        glm::vec3 getPosition() const;
        float getAngleY() const;
        float getAngleX() const;

        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        void moveFront(float delta, std::vector<Obstacle> obstacles);
        void moveLeft(float delta, std::vector<Obstacle> obstacles);


};
