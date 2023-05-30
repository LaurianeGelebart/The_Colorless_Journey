#pragma once
#include "p6/p6.h"

class Texture {
private:
    static int s_nextID;
    int        _slot;
    GLuint     _rendererID;

public:
    explicit Texture(const std::string& path);
    Texture();

    void DeleteTexture();
    void Bind() const;
    void UnBind() const;

    auto getRendererID() const -> GLuint;
    auto getSlot() const -> int;
};