#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"

#include "programs/ColorProgram.hpp"
#include "Object.hpp"
#include "Obstacle.hpp"

#include "IHM.hpp"

class Boid : public Object
{

    private : 
        glm::vec3 _velocity ; 
        float _borne_velocity = 0.001;  
        glm::vec3 _color; 
        glm::vec3 _centerPosition;
        
    public : 
        Boid(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ColorProgram& program, glm::vec3 magicPos);

        glm::vec3 get_velocity() const; 

        void update_position();

        void collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, const IHM ihm);  
        void collision_bords(const IHM ihm); 
        void bounce(const Obstacle& obstacle); 
        void collision_obstacles(const std::vector<Obstacle>& obstacles, const IHM ihm); 
        void collision_boids(const std::vector<Boid>& boids, const IHM ihm);

        void limit_speed(const IHM ihm) ;
        void move(const p6::Context& ctx); 

        void draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color); 

}; 