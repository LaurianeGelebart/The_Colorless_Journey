#include "PanelInfo.hpp"
#include <cmath>
#include "glm/gtc/type_ptr.hpp"

PanelInfo::PanelInfo() = default;

PanelInfo::PanelInfo(const std::vector<ModelPart>& model, PanelProgram& program)
    : _panelProgram(&program), _model(model), _scale(0.04)
{
    this->_position = glm::vec3(0.0f, -1.0f, 0.0f);
}

auto PanelInfo::getDisplay() const -> bool
{
    return this->_isDisplay;
}

auto PanelInfo::getHasBeenDislayed() const -> bool
{
    return this->_hasBeenDislayed;
}

void PanelInfo::appears(const TrackballCamera& viewMatrix)
{
    glm::vec3 viewMatrixPosition = viewMatrix.getPosition();

    float angleX = -viewMatrix.getAngleX();
    float angleY = -viewMatrix.getAngleY();

    float z         = std::sin(glm::radians(90 + angleX))*std::cos(glm::radians(angleY)) * 0.35;
    float y         = std::cos(glm::radians(90 + angleX)) * 0.35;
    float x         = std::sin(glm::radians(angleY))*std::sin(glm::radians(90 - angleX)) * 0.35;
    this->_position = glm::vec3((viewMatrixPosition.x + x), (viewMatrixPosition.y + y), (viewMatrixPosition.z + z));

    this->_angleY = angleY;
    this->_angleX = angleX;

    this->_isDisplay       = true;
    this->_hasBeenDislayed = true;
}

void PanelInfo::disapears()
{
    this->_position.y = -1.0;
    this->_isDisplay  = false;
}

void PanelInfo::draw(const glm::mat4& ViewMatrix, int windowWidth, int windowHeight, std::map<std::string, Material>& materialMap, int color)
{
    this->_panelProgram->_Program.use();

    glm::mat4 MVMatrix = ViewMatrix;
    MVMatrix           = glm::translate(MVMatrix, glm::vec3(this->_position));
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(this->_scale));
    MVMatrix           = glm::rotate(MVMatrix, glm::radians(this->_angleY), glm::vec3(0.f, 1.f, 0.f));
    MVMatrix           = glm::rotate(MVMatrix, glm::radians(this->_angleX), glm::vec3(1.f, 0.f, 0.f));

    glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f);
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    for (auto& face : this->_model)
    {
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);

        glUniformMatrix4fv(this->_panelProgram->uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(this->_panelProgram->uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(this->_panelProgram->uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniform1i(this->_panelProgram->uTexture, materialMap[face.getName()].texture[color].getSlot());

        materialMap[face.getName()].texture[color].Bind();
        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());
        materialMap[face.getName()].texture[color].UnBind();

        glBindVertexArray(0);
    }
}

void PanelInfo::deleteVAO_VBO()
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