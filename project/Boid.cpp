#include "Boid.hpp"
#include <math.h>
#include <iostream>
#include "IHM.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

Boid::Boid(std::vector<ModelPart> model, std::vector<ModelPart> lodModel, ColorProgram& program, glm::vec3 magicPos)
    : _program(&program)
{
    float angle     = (float)(p6::random::integer(0, 360)) * M_PI / 180.0;
    float angleZ    = (float)(p6::random::integer(0, 360)) * M_PI / 180.0;
    this->_velocity = glm::vec3(cos(angle), sin(angle), cos(angleZ));

    this->_centerPosition = magicPos;
    this->_position       = glm::vec3(magicPos + glm::vec3(glm::ballRand(0.2)));

    this->_scale = p6::random::number(0.03, 0.06);
    this->_color = {1.0f, p6::random::number(0.5, 0.8), 0.0};

    this->_models.push_back(model);
    this->_models.push_back(lodModel);
}

glm::vec3 Boid::getVelocity() const
{
    return this->_velocity;
}

void Boid::updatePosition()
{
    this->_position = this->_position + this->_velocity;
}

glm::vec3 Boid::getPosition() const
{
    return this->_position;
}

void Boid::collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, const IHM ihm)
{
    collisionBoids(boids, ihm);
    collisionBords(ihm);
    collisionObstacles(obstacles, ihm);
}

void Boid::collisionBoids(const std::vector<Boid>& boids, const IHM ihm)
{
    glm::vec3 close = glm::vec3(0.f, 0.f, 0.f), pos_avg = glm::vec3(0.f, 0.f, 0.f), dir_avg = glm::vec3(0.f, 0.f, 0.f);
    int       neighboring_boids = 0;

    for (auto& boid : boids)
    {
        if (&boid != this)
        {
            double distance = glm::distance(boid.getPosition(), this->_position);
            if (distance < ihm.getCollisionRadius())
            {
                close += this->_position - boid.getPosition();
            }
            else if (distance < ihm.getDetectionRadius())
            {
                neighboring_boids += 1;
                pos_avg += boid.getPosition();
                dir_avg += boid.getVelocity();
            }
        }
    }
    if (neighboring_boids > 0)
    {
        pos_avg = pos_avg / (float)neighboring_boids;
        dir_avg = dir_avg / (float)neighboring_boids;

        this->_velocity += ((pos_avg - this->_position) * ihm.getCenteringFactor() + (dir_avg - this->_velocity) * ihm.getMatchingFactor());
    }
    this->_velocity += close * ihm.getAvoidFactor();

    limitSpeed(ihm);
}

void Boid::collisionBords(const IHM ihm)
{
    if (this->_position.x > this->_centerPosition.x + ihm.getBoidsArea())
    {
        this->_velocity.x = this->_velocity.x - ihm.getTurnFactor();
    }
    if (this->_position.x < (this->_centerPosition.x - ihm.getBoidsArea()))
    {
        this->_velocity.x = this->_velocity.x + ihm.getTurnFactor();
    }
    if (this->_position.y > 1.5 * ihm.getBoidsArea())
    {
        this->_velocity.y = this->_velocity.y - ihm.getTurnFactor();
    }
    if (this->_position.y < 0.07)
    {
        this->_velocity.y = this->_velocity.y + ihm.getTurnFactor();
    }
    if (this->_position.z > this->_centerPosition.z + ihm.getBoidsArea())
    {
        this->_velocity.z = this->_velocity.z - ihm.getTurnFactor();
    }
    if (this->_position.z < (this->_centerPosition.z - ihm.getBoidsArea()))
    {
        this->_velocity.z = this->_velocity.z + ihm.getTurnFactor();
    }
}

void Boid::collisionObstacles(const std::vector<Obstacle>& obstacles, const IHM ihm)
{
    for (auto& obstacle : obstacles)
    {
        double distance = glm::distance(obstacle.getPosition(), this->_position);
        if (distance < 0.05)
        {
            this->bounce(obstacle);
        }
    }
    limitSpeed(ihm);
}

void Boid::bounce(const Obstacle& obstacle)
{
    glm::vec3 normal = glm::vec3(this->_position.x - obstacle.getPosition().x, this->_position.y - obstacle.getPosition().y, this->_position.z - obstacle.getPosition().z);
    normal           = glm::normalize(normal);
    this->_velocity += normal * 0.01f;
}

void Boid::limitSpeed(const IHM ihm)
{
    float speed = std::sqrt(this->_velocity.x * this->_velocity.x + this->_velocity.y * this->_velocity.y + this->_velocity.z * this->_velocity.z);

    if (speed < ihm.getSpeed() - this->_borne_velocity)
    {
        speed = ihm.getSpeed() - this->_borne_velocity;
    }
    if (speed < ihm.getSpeed() - this->_borne_velocity)
    {
        this->_velocity = (this->_velocity / speed) * (ihm.getSpeed() - this->_borne_velocity);
    }
    if (speed > ihm.getSpeed() + this->_borne_velocity)
    {
        this->_velocity = (this->_velocity / speed) * (ihm.getSpeed() + this->_borne_velocity);
    }
}

void Boid::draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color)
{
    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix           = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(this->_scale));

    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    for (auto& face : this->_models[this->_lod])
    {
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_program->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_program->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_program->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));

        glUniform1f(this->_program->uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program->uKd, 1, glm::value_ptr(this->_color));
        glUniform3fv(this->_program->uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));

        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());

        glBindVertexArray(0);
    }
}

void Boid::checkLOD(glm::vec3 fireflyPosition)
{
    double distance = glm::distance(fireflyPosition, this->_position);
    this->_lod      = (distance > 0.7) ? 1 : 0;
}

void Boid::deleteVAO_VBO()
{
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        for (auto& face : this->_models[i])
        {
            GLuint vbo = face.getVBO();
            GLuint ibo = face.getIBO();
            GLuint vao = face.getVAO();
            glDeleteBuffers(0, &vbo);
            glDeleteBuffers(0, &ibo);
            glDeleteVertexArrays(0, &vao);
        }
    }
}
