#include <iostream>
#include <math.h>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/random.hpp"

#include "Boid.hpp"
#include "IHM.hpp"


Boid::Boid(std::vector<FacesGroup> model, std::vector<FacesGroup> lodModel, ColorProgram& program, glm::vec3 magicPos)
:Object(model, lodModel, program) 
{
    this->_centerPosition = magicPos;
    this->_position = glm::vec3(magicPos + glm::vec3(glm::ballRand(0.2)));
    float angle = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    float angleZ = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    this->_velocity = glm::vec3(cos(angle), sin(angle) ,cos(angleZ)) ;
    this->_scale = p6::random::number(0.003, 0.006);
    this->_color = {1.0f, p6::random::number(0.5, 0.8), 0.0} ;
}

glm::vec3 Boid::get_velocity() const
{
    return this->_velocity ; 
}

void Boid::update_position() 
{
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
        if(distance < 0.05){
            this->bounce(obstacle); 
        }
    }
    limit_speed(ihm); 
} 

void Boid::bounce(const Obstacle &obstacle) 
{
    glm::vec3 normal = glm::vec3(this->_position.x - obstacle.getPosition().x , this->_position.y - obstacle.getPosition().y , this->_position.z - obstacle.getPosition().z);
    normal = glm::normalize(normal); 
    this->_velocity += normal*0.01f; 
}


void Boid::limit_speed(const IHM ihm)
{
    float speed = std::sqrt(this->_velocity.x*this->_velocity.x + this->_velocity.y*this->_velocity.y + this->_velocity.z*this->_velocity.z); 
    
    if(speed < ihm.getSpeed()-this->_borne_velocity){
        speed = ihm.getSpeed()-this->_borne_velocity ;  
    }
    if (speed < ihm.getSpeed()-this->_borne_velocity) {
        this->_velocity = (this->_velocity/speed)*(ihm.getSpeed()-this->_borne_velocity) ;       
    }
    if (speed > ihm.getSpeed()+this->_borne_velocity) {
        this->_velocity = (this->_velocity/speed)*(ihm.getSpeed()+this->_borne_velocity) ; 
    }
}


void Boid::draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color)
{  
    this->_boidProgram->_Program.use() ; 

    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix = glm::rotate(MVMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


// light 
    glm::mat4 VLightMatrix = ViewMatrix;
    glm::vec3 lightPos = glm::vec3( (VLightMatrix)*glm::vec4(0,0,0,1) );


//shadow part
    // glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	// glm::mat4 lightView = glm::lookAt(20.0f * lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// glm::mat4 lightProjection = orthgonalProjection * lightView;

	// shadowMapProgram.Activate();
	// glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
// ossekour 


    for(auto& face : this->_models[this->_lod] ){
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_boidProgram->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_boidProgram->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_boidProgram->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
           
        glUniform1f(this->_boidProgram->uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_boidProgram->uKd, 1, glm::value_ptr(this->_color));
        glUniform3fv(this->_boidProgram->uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));
        glUniform3fv(this->_boidProgram->uLightPos_vs, 1, glm::value_ptr(lightPos));
        glUniform3fv(this->_boidProgram->uLightIntensity, 1, glm::value_ptr(glm::vec3(0.1)));


        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());


		glBindVertexArray(0) ;
    }
}