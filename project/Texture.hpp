#pragma once
#include "p6/p6.h"

class Texture {
private:
    static int s_nextID;
    int        _slot;
    GLuint     _rendererID;

public:
    Texture(std::string path);
    Texture();

    void DeleteTexture();
    void Bind() const;
    void UnBind() const;

    GLuint getRendererID() const;
    int    getSlot() const;
};