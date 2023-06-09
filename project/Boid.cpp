#include "Boid.hpp"
#include <cmath>
#include <iostream>
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"

Boid::Boid(const std::vector<ModelPart>& model, const std::vector<ModelPart>& lodModel, ColorProgram& program, glm::vec3 magicPos)
    : _centerPosition(magicPos), _program(&program), _scale(p6::random::number(0.03, 0.06))
{
    float angle     = static_cast<float>((p6::random::integer(0, 360)) * M_PI / 180.f);
    float angleZ    = static_cast<float>((p6::random::integer(0, 360)) * M_PI / 180.f);
    this->_velocity = glm::vec3(std::cos(angle), std::sin(angle), std::cos(angleZ));
    this->_position = glm::vec3(magicPos + glm::vec3(glm::ballRand(0.2)));
    this->_color    = {1.0f, p6::random::number(0.5, 0.8), 0.0};
    this->_models.push_back(model);
    this->_models.push_back(lodModel);
}

auto Boid::getVelocity() const -> glm::vec3
{
    return this->_velocity;
}

void Boid::updatePosition()
{
    this->_position = this->_position + this->_velocity;
}

auto Boid::getPosition() const -> glm::vec3
{
    return this->_position;
}

void Boid::collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, const IHM& ihm)
{
    collisionBoids(boids, ihm);
    collisionBords(ihm);
    collisionObstacles(obstacles, ihm);
    collisionBox(ihm);
}

void Boid::collisionBoids(const std::vector<Boid>& boids, const IHM& ihm)
{
    glm::vec3 close             = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 pos_avg           = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 dir_avg           = glm::vec3(0.f, 0.f, 0.f);
    int       neighboring_boids = 0;

    for (const auto& boid : boids)
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
        pos_avg = pos_avg / static_cast<float>(neighboring_boids);
        dir_avg = dir_avg / static_cast<float>(neighboring_boids);

        this->_velocity += ((pos_avg - this->_position) * ihm.getCenteringFactor() + (dir_avg - this->_velocity) * ihm.getMatchingFactor());
    }
    this->_velocity += close * ihm.getAvoidFactor();

    limitSpeed(ihm);
}

void Boid::collisionBords(const IHM& ihm)
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
    limitSpeed(ihm);
}

void Boid::collisionObstacles(const std::vector<Obstacle>& obstacles, const IHM& ihm)
{
    for (const auto& obstacle : obstacles)
    {
        double distance = glm::distance(obstacle.getPosition(), this->_position);
        if (distance < obstacle.get_radius())
        {
            this->bounce(obstacle.getPosition());
        }
    }
    limitSpeed(ihm);
}

void Boid::collisionBox(const IHM& ihm)
{
    float margin = 0.3;
    float width  = 2.f;
    float length = 2.f;

    if (this->_position.x > width - margin)
    {
        this->_velocity.x = this->_velocity.x - ihm.getTurnFactor();
    }
    if (this->_position.x < -width + margin)
    {
        this->_velocity.x = this->_velocity.x + ihm.getTurnFactor();
    }
    if (this->_position.z > length - margin)
    {
        this->_velocity.z = this->_velocity.z - ihm.getTurnFactor();
    }
    if (this->_position.z < -length + margin)
    {
        this->_velocity.z = this->_velocity.z + ihm.getTurnFactor();
    }
    limitSpeed(ihm);
}

void Boid::bounce(const glm::vec3& obstaclePosition)
{
    glm::vec3 normal = glm::vec3(this->_position.x - obstaclePosition.x, this->_position.y - obstaclePosition.y, this->_position.z - obstaclePosition.z);
    normal           = glm::normalize(normal);
    this->_velocity += normal * 0.01f;
}

void Boid::limitSpeed(const IHM& ihm)
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

void Boid::draw(const glm::mat4& ViewMatrix, int windowWidth, int windowHeight, std::map<std::string, Material>& materialMap)
{
    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix           = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(this->_scale));

    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    for (auto& face : this->_models[this->_lod])
    {
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_program->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_program->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_program->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));

        glUniform1f(this->_program->uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program->uKd, 1, glm::value_ptr(this->_color.as_straight_vec3()));
        glUniform3fv(this->_program->uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));

        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());

        glBindVertexArray(0);
    }
}

void Boid::checkLOD(const glm::vec3& fireflyPosition)
{
    double distance = glm::distance(fireflyPosition, this->_position);
    this->_lod      = (distance > 0.7) ? 1 : 0;
}

void Boid::deleteVAO_VBO()
{
    for (auto& _model : this->_models)
    {
        for (auto& face : _model)
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
