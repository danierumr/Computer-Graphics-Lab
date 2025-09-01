#pragma once
#include "../render/Shader.h"
#include "Texture.h"
#include <vector>

class Material {
public:

    Material();
    ~Material();

    void CreateTexture(const std::string& path, GLenum type = GL_TEXTURE_2D, const std::string& uniformName = "diffuseTex", int unit = 0);
    
    void AddTexture(const Texture* texture, const std::string& uniformName, int unit);

    void Use(const Shader* shader) const;

    void SetBaseColor(glm::vec3 color) { mBaseColor = color; }

private:

    struct TextureSlot {
        const Texture* texture;
        std::string uniformName;
        int unit;
    };

    std::vector<TextureSlot> textures;
    glm::vec3 mBaseColor;

};
