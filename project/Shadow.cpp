#include "Shadow.hpp"
#include "glm/gtc/type_ptr.hpp"

Shadow::Shadow() = default;

void Shadow::initFBO()
{
    glGenFramebuffers(1, &_shadowMapFBO);

    glGenTextures(1, &this->_shadowMap);
    glBindTexture(GL_TEXTURE_2D, this->_shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->_shadowMapWidth, this->_shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float clampColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

    glBindFramebuffer(GL_FRAMEBUFFER, this->_shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_shadowMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow::renderShadow(Object& model, const glm::vec3& ViewMatrix, const glm::vec3& VLightMatrix)
{
    updateMatrix(model, ViewMatrix, VLightMatrix);
    drawShadow(model);
}

void Shadow::updateMatrix(Object& model, const glm::vec3& ViewMatrix, const glm::vec3& VLightMatrix)
{
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->_nearPlane, this->_farPlane);
    glm::mat4 lightView       = glm::lookAt(ViewMatrix, glm::vec3(VLightMatrix), glm::vec3(0.0f, 1.0f, 0.0f));

    this->_lightSpaceMatrix = lightProjection * lightView;

    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), model.getPosition());
    MVMatrix           = glm::scale(MVMatrix, glm::vec3(model.getScale()));
    MVMatrix           = glm::rotate(MVMatrix, glm::radians(model.getAngleY()), glm::vec3(0.f, 1.f, 0.f));

    this->_mVMatrix = MVMatrix;
}

void Shadow::drawShadow(Object& model)
{
    this->_shadowProgram._Program.use();

    glUniformMatrix4fv(this->_shadowProgram.uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(this->_lightSpaceMatrix));
    glUniformMatrix4fv(this->_shadowProgram.uModel, 1, GL_FALSE, glm::value_ptr(this->_mVMatrix));
    glUniform1i(this->_shadowProgram.uDepthMap, this->_shadowMap);

    glViewport(0, 0, this->_shadowMapWidth, this->_shadowMapHeight);

    glBindFramebuffer(GL_FRAMEBUFFER, this->_shadowMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (const auto& face : model.getModel())
    {
        GLuint vao = face.getVAO();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, face.getVertextCount());
        glBindVertexArray(0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1920, 1080);
}
