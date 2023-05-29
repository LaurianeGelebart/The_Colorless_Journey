#include "Texture.hpp"

int Texture::s_nextID = 0; 

Texture::Texture()
{
    this->_slot = s_nextID++;
    img::Image image =  p6::load_image_buffer("./assets/textures/none.png") ;   

    glGenTextures(1, &(this->_rendererID)); 
    glBindTexture(GL_TEXTURE_2D, this->_rendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(std::string path)
{
    this->_slot = s_nextID++;
    img::Image image =  p6::load_image_buffer(path) ;   

    glGenTextures(1, &(this->_rendererID)); 
    glBindTexture(GL_TEXTURE_2D, this->_rendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::DeleteTexture()
{
    glDeleteTextures(1, &this->_rendererID);
}

void Texture::Bind() const
{
    if(this->_slot >= 0){
        glActiveTexture(GL_TEXTURE0 + this->_slot);
        glBindTexture(GL_TEXTURE_2D,this->_rendererID);
    }
}

void Texture::UnBind() const
{
    if(this->_slot >= 0){
        glActiveTexture(GL_TEXTURE0 + this->_slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

int Texture::getSlot() const 
{
    return this->_slot ; 
}

GLuint Texture::getRendererID() const 
{
    return this->_rendererID ; 
}