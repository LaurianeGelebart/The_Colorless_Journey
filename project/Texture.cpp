#include "Texture.hpp"
// #include "vender/stb_image/stb_image.hpp"

Texture::Texture()
: _slot(-1){}

Texture::Texture(std::string path, int slot)
:  _slot(slot)
{
    img::Image image =  p6::load_image_buffer(path) ;   

    glGenTextures(1, &(this->_rendererID)); //debug
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
    // std::cout << (int)(GL_TEXTURE0+5 == GL_TEXTURE5) << "\n"; 
        glActiveTexture(GL_TEXTURE0 + this->_slot);
        glBindTexture(GL_TEXTURE_2D,this->_rendererID);
    }
}

void Texture::UnBind() const
{
    if(this->_slot >= 0){
    // std::cout << _slot << "\n"; 
        glActiveTexture(GL_TEXTURE0 + this->_slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}