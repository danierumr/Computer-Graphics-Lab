#pragma once
#include "../render/Shader.h"
#include "Texture.h"
#include <memory>

class Material {
public:

    Material();
    ~Material() = default;

    // Set or override textures (empty path -> use default)
    void SetDiffuse(const std::string& path = "");
    void SetSpecular(const std::string& path = "");
    void SetEmission(const std::string& path = "");

    // Upload uniforms & bind textures
    void Use(const Shader* shader) const;

    // Optional properties used by your shader
    void SetBaseColor(const glm::vec3& c) { mBaseColor = c; }
    void SetShininess(float s) { mShininess = s; }

    bool GetIsEmissive() { return isEmissive; }

private:

    static std::shared_ptr<Texture> sDefaultTex;    // loaded from default_mat.jpg once

    std::shared_ptr<Texture> mDiffuseTex;
    std::shared_ptr<Texture> mSpecularTex;
    std::shared_ptr<Texture> mEmissionTex;

    bool isEmissive;

    glm::vec3 mBaseColor {1.0f, 1.0f, 1.0f};
    float     mShininess {32.0f};

};