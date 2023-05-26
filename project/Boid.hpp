#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"

#include "programs/ColorProgram.hpp"
#include "FacesGroup.hpp"
#include "Object.hpp"
#include "Obstacle.hpp"

#include "IHM.hpp"

class Boid 
{

    private : 
        glm::vec3 _velocity ; 
        float _borne_velocity = 0.001;  
        glm::vec3 _color; 
        glm::vec3 _centerPosition;
        ColorProgram* _program;
        std::vector<std::vector<FacesGroup>> _models;
        glm::vec3 _position ; 
        float _scale  = 0.1 ; 
        int _lod = 1; 

        void collisionBords(const IHM ihm); 
        void bounce(const Obstacle& obstacle); 
        void collisionObstacles(const std::vector<Obstacle>& obstacles, const IHM ihm); 
        void collisionBoids(const std::vector<Boid>& boids, const IHM ihm);

        void limitSpeed(const IHM ihm) ;
        void move(const p6::Context& ctx); 

    public : 
        Boid(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ColorProgram& program, glm::vec3 magicPos);
        
        glm::vec3 getPosition() const; 
        glm::vec3 getVelocity() const; 

        void updatePosition();
        void collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, const IHM ihm);  
        void draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color); 
        
        void checkLOD(glm::vec3 gaspardPosition);
        void deleteVAO_VBO();

}; 