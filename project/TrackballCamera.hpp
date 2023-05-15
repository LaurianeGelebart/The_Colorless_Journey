#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

#include "Material.hpp"

static int normalizeAngle(int angle);


class TrackballCamera 
{

    private:
        float _distance = 0.5; 
        float _angleX = 11.f; 
        float _angleY = 0.f; 

        Vec _position;


        bool checkMovingPosition(Vec position) const;
        bool checkRotatingAngleX(float angle) const;
        bool checkRotatingAngleY(float angle) const;

    public:
        TrackballCamera(); 

        glm::mat4 getViewMatrix() const ;
        Vec getPosition() const;
        float getAngleY() const;

        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        void moveFront(float delta);
        void moveLeft(float delta);


};

