#pragma once

#include <iostream>
#include <vector>
#include "p6/p6.h"

class Light {
protected:
    Light(glm::vec3 position);
    glm::vec3 _position;
    glm::vec3 _environmentPosition;

public:
    Light();
    glm::vec3    getPosition() const;
    void         setPosition(glm::vec3 position);
    virtual void update(glm::mat4 viewMatrix) = 0;
};

class PointLight : public Light {
public:
    PointLight(glm::vec3 position);
    void update(glm::mat4 viewMatrix) override;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 position);
    void update(glm::mat4 viewMatrix) override;
};
