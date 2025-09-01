#pragma once
#include <glad/glad.h>
#include <string>
#include "../third_party/stb_image.h"

class Texture {
public:
    Texture(const std::string& path, GLenum type = GL_TEXTURE_2D);

    void Bind(GLenum unit = 0) const;

private:
    unsigned int ID;
};
