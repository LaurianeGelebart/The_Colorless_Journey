#include "Object.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "TrackballCamera.hpp"
#include "glm/gtc/random.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"

Object::Object(std::vector<ModelPart> model, ObjectProgram& program)
    : _program(&program), _model(model)
{}

Object::Object() {}

glm::vec3 Object::getPosition() const
{
    return this->_position;
}

float Object::getAngleY() const
{
    return this->_angleY;
}

float Object::getScale() const
{
    return this->_scale;
}

std::vector<ModelPart>& Object::getModel()
{
    return this->_model;
}

void Object::draw(const glm::mat4 ViewMatrix, const int windowWidth, const int windowHeight, std::map<std::string, Material>& materialMap, glm::vec3 wandererPos, int color)
{
    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix           = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix           = glm::rotate(MVMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));

    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glUniformMatrix4fv(this->_program->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(this->_program->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(this->_program->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));

    for (auto& face : this->_model)
    {
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniform1i(this->_program->uTexture, materialMap[face.getName()].texture[color].getSlot());
        glUniform1f(this->_program->uShininess, materialMap[face.getName()].shininess);
        glUniform3fv(this->_program->uKd, 1, glm::value_ptr(materialMap[face.getName()].Kd));
        glUniform3fv(this->_program->uKs, 1, glm::value_ptr(materialMap[face.getName()].Ks));

        materialMap[face.getName()].texture[color].Bind();
        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());
        materialMap[face.getName()].texture[color].UnBind();

        glBindVertexArray(0);
    }
}

void Object::deleteVAO_VBO()
{
    for (auto& face : this->_model)
    {
        GLuint vbo = face.getVBO();
        GLuint ibo = face.getIBO();
        GLuint vao = face.getVAO();
        glDeleteBuffers(0, &vbo);
        glDeleteBuffers(0, &ibo);
        glDeleteVertexArrays(0, &vao);
    }
}
