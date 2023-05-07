#pragma once

#include <cstdlib>
#include <vector>
#include "Obstacle.hpp"

#include "Object.hpp"
#include "p6/p6.h"

class Boid : public Object
{

    private : 
        Vec _velocity ; 
        float _borne_velocity ;  
        p6::Color _color;

        
    public : 
        Boid(std::vector<FacesGroup> facesGroup, ObjectProgram& program);

        Vec get_velocity() const; 

        void update_position();
        void set_color(p6::Color color);

        void collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, IHM ihm, p6::Context& ctx);  
        void collision_bords(IHM ihm, p6::Context& ctx); 
        void bounce(Obstacle obstacle); 
        void collision_obstacles(const std::vector<Obstacle>& obstacles, IHM ihm); 
        void collision_boids(const std::vector<Boid>& boids, IHM ihm);

        void limit_speed(IHM ihm) ;
        double distance(Vec pos) ;
        void move(p6::Context& ctx); 

}; 