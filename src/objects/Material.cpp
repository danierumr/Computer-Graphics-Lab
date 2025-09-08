#include "Material.h"

// One-time default texture (your fallback)
std::shared_ptr<Texture> Material::sDefaultTex = nullptr;

Material::Material() {
    if (!sDefaultTex) {
        // Make sure this path points to your actual asset
        sDefaultTex = std::make_shared<Texture>("../assets/default_mat.jpg", GL_TEXTURE_2D);
    }
    // By default, both slots use the fallback
    mDiffuseTex  = sDefaultTex;
    mSpecularTex = sDefaultTex; // If you prefer “no specular” by default, bind a black texture instead
    isEmissive = false;
}

void Material::SetDiffuse(const std::string& path) {
    if (path.empty()) mDiffuseTex = sDefaultTex;
    else              mDiffuseTex = std::make_shared<Texture>(path, GL_TEXTURE_2D);
}

void Material::SetSpecular(const std::string& path) {
    if (path.empty()) mSpecularTex = sDefaultTex;   // consider a black 1×1 as a nicer default
    else              mSpecularTex = std::make_shared<Texture>(path, GL_TEXTURE_2D);
}

void Material::SetEmission(const std::string& path) {
    if (path.empty()) return;
    
    mEmissionTex = std::make_shared<Texture>(path, GL_TEXTURE_2D);
    isEmissive = true;

}

void Material::Use(const Shader* shader) const {

    // Bind textures to fixed units (match your GLSL)
    mDiffuseTex->Bind(0);
    shader->setInt("material.diffuse", 0);

    mSpecularTex->Bind(1);
    shader->setInt("material.specular", 1);

    // Upload scalar uniforms
    shader->setFloat("material.shininess", mShininess);
    shader->setVec3("material.baseColor", mBaseColor);

    // Emission
    shader->setBool("material.emissive", isEmissive);
    if (mEmissionTex) {
        mEmissionTex->Bind(2);
        shader->setInt("material.emission", 2);
    }
}
