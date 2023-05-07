#include "IHM.hpp"
#include "Boid.hpp"
#include "glm/gtc/random.hpp"
#include <iostream>
#include <math.h>


Boid::Boid(std::vector<FacesGroup> facesGroup, ObjectProgram& program)
:Object(facesGroup, program) 
{
    this->_position = Vec(glm::ballRand(2.0)) ;
    this->_borne_velocity = 0.003;  
    float angle = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    float angleZ = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    this->_velocity = Vec(cos(angle), sin(angle) ,cos(angleZ)) ;
    this->_color = {0.5f, 0.2f, 0.2f} ; 
}

Vec Boid::get_velocity() const
{
    return this->_velocity ; 
}

void Boid::update_position() 
{
    this->_position =  this->_position + this->_velocity ;
}

void Boid::set_color(p6::Color color)
{
    this->_color = color ; 
}


void Boid::collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, IHM ihm, p6::Context& ctx)
{
    collision_boids(boids, ihm); 
    collision_obstacles(obstacles, ihm); 
    collision_bords(ihm, ctx); 
}

void Boid::collision_boids(const std::vector<Boid>& boids, IHM ihm)
{
    Vec close=Vec(0.f, 0.f, 0.f), pos_avg=Vec(0.f, 0.f, 0.f), dir_avg=Vec(0.f, 0.f, 0.f) ; 
    int neighboring_boids = 0 ; 

   for (auto boid : boids){ 
        double distance = glm::distance(boid.get_position(),this->_position);     
        if(&boid != this){ 
            if (distance < ihm.get_collision_radius() ){ 
                close += this->_position - boid.get_position();
            }  
            else if(distance < ihm.get_detection_radius() ) {
                neighboring_boids += 1 ;
                pos_avg += boid.get_position() ;
                dir_avg += boid.get_velocity() ;
            } 
        }
   }
   if (neighboring_boids > 0) {
        pos_avg = pos_avg/(float)neighboring_boids ;
        dir_avg = dir_avg/(float)neighboring_boids ;

        this->_velocity += (
            (pos_avg - this->_position)*ihm.get_centering_factor() + 
            (dir_avg - this->_velocity)*ihm.get_matching_factor()) ;  
    }
    this->_velocity += close*ihm.get_avoid_factor();

    limit_speed(ihm); 
}

void Boid::collision_bords(IHM ihm, p6::Context& ctx)
{
    if (this->_position.x > 2*(ctx.aspect_ratio()-ctx.aspect_ratio()*0.2)){ // TODO dont hardcode the 2: https://julesfouchy.github.io/p6-docs/tutorials/the-coordinate-system
         this->_velocity.x = this->_velocity.x - ihm.get_turn_factor(); 
    }
    if (this->_position.x < 2*(-ctx.aspect_ratio()+ctx.aspect_ratio()*0.2 )) {
         this->_velocity.x = this->_velocity.x + ihm.get_turn_factor(); 
    }
    if (this->_position.y > 2*(ctx.aspect_ratio()-ctx.aspect_ratio()*0.2)){
         this->_velocity.y = this->_velocity.y - ihm.get_turn_factor(); 
    } 
    if (this->_position.y < 2*(-ctx.aspect_ratio()+ctx.aspect_ratio()*0.2)){
         this->_velocity.y = this->_velocity.y +  ihm.get_turn_factor(); 
    }
    if (this->_position.z > 2*(ctx.aspect_ratio()-ctx.aspect_ratio()*0.2)){
         this->_velocity.z = this->_velocity.z - ihm.get_turn_factor(); 
    } 
    if (this->_position.z < 2*(-ctx.aspect_ratio()+ctx.aspect_ratio()*0.2)){
         this->_velocity.z = this->_velocity.z +  ihm.get_turn_factor(); 
    }
}

void Boid::collision_obstacles(const std::vector<Obstacle>& obstacles, IHM ihm)
{
    for(auto obstacle : obstacles){
        double distance = glm::distance(obstacle.get_position(), this->_position);
        //    std::cout << " x : " << obstacles[i].get_position().x << " y : " << obstacles[i].get_position().y << " z : " << obstacles[i].get_position().z << " Distance : " << distance <<"\n"; 
        
        if(distance < 2){
        // if(distance < obstacles[i].get_radius()){
            // if (this->_position.x > obstacles[i].get_position().x){
            //     this->_velocity.x = this->_velocity.x + ihm.get_turn_factor()*10; 
            // }
            // if (this->_position.x < obstacles[i].get_position().x) {
            //     this->_velocity.x = this->_velocity.x - ihm.get_turn_factor()*10; 
            // }
            // if (this->_position.y > obstacles[i].get_position().y){
            //     this->_velocity.y = this->_velocity.y + ihm.get_turn_factor()*10; 
            // } 
            // if (this->_position.y < obstacles[i].get_position().y){
            //     this->_velocity.y = this->_velocity.y -  ihm.get_turn_factor()*10; 
            // }
            this->bounce(obstacle); 
        }
    }
    limit_speed(ihm); 
} 

void Boid::bounce(Obstacle obstacle)
{
    Vec normal = Vec(this->_position.x - obstacle.get_position().x , this->_position.y - obstacle.get_position().y , this->_position.z - obstacle.get_position().z);
    normal = glm::normalize(normal); 
   // Vec T = Vec(normal.y , -normal.x, 0.) ; 
    // float vt = glm::dot(this->_velocity, T); 
    // float vn = glm::dot(this->_velocity, 2.f*normal); 
    this->_velocity += normal*0.01f; //( vt*T - vn*normal ); 
}


void Boid::limit_speed(IHM ihm)
{
    float speed = std::sqrt(this->_velocity.x*this->_velocity.x + this->_velocity.y*this->_velocity.y + this->_velocity.z*this->_velocity.z); 
    // TODO use glm::length
    
    if(speed < ihm.get_speed()-this->_borne_velocity) speed = ihm.get_speed()-this->_borne_velocity ;  

    if (speed < ihm.get_speed()-this->_borne_velocity) {
        this->_velocity = (this->_velocity/speed)*(ihm.get_speed()-this->_borne_velocity) ;       
    }
    if (speed > ihm.get_speed()+this->_borne_velocity) {
        this->_velocity = (this->_velocity/speed)*(ihm.get_speed()+this->_borne_velocity) ; 
    }
}


double Boid::distance(Vec pos)
{
    return std::sqrt( std::pow( this->_position.x - pos.x ,2)  +  std::pow( this->_position.y - pos.y ,2) ) ; 
}