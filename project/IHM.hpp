#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"

#include "FacesGroup.hpp"
// #include "Obstacle.hpp"
// #include "Boid.hpp"
#include "ObjectProgram.hpp"


class IHM {

    private : 
        float _turn_factor = 0.0005  ; 
        float _matching_factor = 0.03 ;
        float _avoid_factor = 0.005 ; 
        float _centering_factor = 0.0005 ; 
        float _collision_radius = 0.5 ; 
        float _detection_radius = 1.0 ; 
        float _speed = 0.1 ; 
        int _nb_obstacles = 60 ; 
        int _nb_boids = 40 ; 
        
    public : 
        IHM(); 
        void draw(); 
        // void add_or_remove_boids(std::vector<Boid> &boids, ObjectProgram &program, std::vector<FacesGroup> &model, Vec magicPos); 
        // void add_or_remove_obstacles(std::vector<Obstacle> &obstacles, ObjectProgram &program, std::vector<FacesGroup> &model); 

        float get_turn_factor()  ; 
        float get_matching_factor() ;  
        float get_avoid_factor() ; 
        float get_centering_factor() ; 
        float get_collision_radius() ; 
        float get_detection_radius() ; 
        float get_speed() ;
        int get_nb_obstacles() ; 
        int get_nb_boids() ;

}; 