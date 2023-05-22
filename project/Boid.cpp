#include "Boid.hpp"
#include "glm/gtc/random.hpp"
#include <iostream>
#include <math.h>

#include "IHM.hpp"


Boid::Boid(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ObjectProgram& program, glm::vec3 magicPos)
:Object(model, lodModel, program) 
{
    this->_centerPosition = magicPos;
    this->_position = glm::vec3(magicPos + glm::vec3(glm::ballRand(0.2)));
    float angle = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    float angleZ = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    this->_velocity = glm::vec3(cos(angle), sin(angle) ,cos(angleZ)) ;
    this->_scale = p6::random::number(0.005, 0.01);
}

glm::vec3 Boid::get_velocity() const
{
    return this->_velocity ; 
}

void Boid::update_position() 
{
    // std::cout << this->_position.x << " - "<< this->_position.z << "\n";
    this->_position =  this->_position + this->_velocity ;
}


void Boid::collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, const IHM ihm)
{
    collision_boids(boids, ihm); 
    collision_bords(ihm); 
    collision_obstacles(obstacles, ihm); 
}

void Boid::collision_boids(const std::vector<Boid>& boids, const IHM ihm)
{
    glm::vec3 close=glm::vec3(0.f, 0.f, 0.f), pos_avg=glm::vec3(0.f, 0.f, 0.f), dir_avg=glm::vec3(0.f, 0.f, 0.f) ; 
    int neighboring_boids = 0 ; 

   for (auto& boid : boids){ 
        if(&boid != this){ 
            double distance = glm::distance(boid.getPosition(),this->_position);     
            if (distance < ihm.getCollisionRadius() ){ 
                close += this->_position - boid.getPosition();
            }  
            else if(distance < ihm.getDetectionRadius() ) {
                neighboring_boids += 1 ;
                pos_avg += boid.getPosition() ;
                dir_avg += boid.get_velocity() ;
            } 
        }
   }
   if (neighboring_boids > 0) {
        pos_avg = pos_avg/(float)neighboring_boids ;
        dir_avg = dir_avg/(float)neighboring_boids ;

        this->_velocity += (
            (pos_avg - this->_position)*ihm.getCenteringFactor() + 
            (dir_avg - this->_velocity)*ihm.getMatchingFactor()) ;  
    }
    this->_velocity += close*ihm.getAvoidFactor();

    limit_speed(ihm); 
}

void Boid::collision_bords(const IHM ihm)
{
    if (this->_position.x > this->_centerPosition.x + ihm.getBoidsArea()){ 
         this->_velocity.x = this->_velocity.x - ihm.getTurnFactor(); 
    }
    if (this->_position.x < (this->_centerPosition.x -ihm.getBoidsArea())) {
         this->_velocity.x = this->_velocity.x + ihm.getTurnFactor(); 
    }
    if (this->_position.y > 1.5*ihm.getBoidsArea()){
         this->_velocity.y = this->_velocity.y - ihm.getTurnFactor(); 
    } 
    if (this->_position.y < 0.07){
         this->_velocity.y = this->_velocity.y +  ihm.getTurnFactor(); 
    }
    if (this->_position.z > this->_centerPosition.z + ihm.getBoidsArea()){
         this->_velocity.z = this->_velocity.z - ihm.getTurnFactor(); 
    } 
    if (this->_position.z < (this->_centerPosition.z - ihm.getBoidsArea())){
         this->_velocity.z = this->_velocity.z +  ihm.getTurnFactor(); 
    }
}

void Boid::collision_obstacles(const std::vector<Obstacle>& obstacles, const IHM ihm)
{
    for(auto& obstacle : obstacles){
        double distance = glm::distance(obstacle.getPosition(), this->_position);

        // std::cout << "boid " << distance << "\n";
        if(distance < 0.05){
        // if(distance < obstacles[i].get_radius()){
            // if (this->_position.x > obstacles[i].getPosition().x){
            //     this->_velocity.x = this->_velocity.x + ihm.getTurnFactor()*10; 
            // }
            // if (this->_position.x < obstacles[i].getPosition().x) {
            //     this->_velocity.x = this->_velocity.x - ihm.getTurnFactor()*10; 
            // }
            // if (this->_position.y > obstacles[i].getPosition().y){
            //     this->_velocity.y = this->_velocity.y + ihm.getTurnFactor()*10; 
            // } 
            // if (this->_position.y < obstacles[i].getPosition().y){
            //     this->_velocity.y = this->_velocity.y -  ihm.getTurnFactor()*10; 
            // }
            this->bounce(obstacle); 
        }
    }
    limit_speed(ihm); 
} 

void Boid::bounce(const Obstacle &obstacle) 
{
    glm::vec3 normal = glm::vec3(this->_position.x - obstacle.getPosition().x , this->_position.y - obstacle.getPosition().y , this->_position.z - obstacle.getPosition().z);
    normal = glm::normalize(normal); 
   // glm::vec3 T = glm::vec3(normal.y , -normal.x, 0.) ; 
    // float vt = glm::dot(this->_velocity, T); 
    // float vn = glm::dot(this->_velocity, 2.f*normal); 
    this->_velocity += normal*0.01f; //( vt*T - vn*normal ); 
}


void Boid::limit_speed(const IHM ihm)
{
    float speed = std::sqrt(this->_velocity.x*this->_velocity.x + this->_velocity.y*this->_velocity.y + this->_velocity.z*this->_velocity.z); 
    // TODO use glm::length
    
    if(speed < ihm.getSpeed()-this->_borne_velocity) speed = ihm.getSpeed()-this->_borne_velocity ;  

    if (speed < ihm.getSpeed()-this->_borne_velocity) {
        this->_velocity = (this->_velocity/speed)*(ihm.getSpeed()-this->_borne_velocity) ;       
    }
    if (speed > ihm.getSpeed()+this->_borne_velocity) {
        this->_velocity = (this->_velocity/speed)*(ihm.getSpeed()+this->_borne_velocity) ; 
    }
}
