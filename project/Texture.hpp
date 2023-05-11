#pragma once
#include "p6/p6.h"

class Texture {
private:
    // GLuint _rendererID;
    // unsigned int _slot;

public:
    Texture(std::string path, int slot=-1);
    Texture();

    void DeleteTexture();
    void Bind() const;
    void UnBind() const;


    GLuint _rendererID;
    int _slot;

};