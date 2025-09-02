#include "Material.h"

Material::Material() {
    // Inicialização, se necessário
    mBaseColor = glm::vec3(1.0f, 1.0f, 1.0f);

    mAmbient = glm::vec3(1.0f, 1.0f, 1.0f);
    mDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    mSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
    mShininess = 32;
}

Material::~Material() {
    for (auto& t : textures) {
        delete t.texture; // só se você alocou com new
    }
}

void Material::AddTexture(const Texture* tex, const std::string& uniformName, int unit) {
    textures.push_back({tex, uniformName, unit});
}

void Material::Use(const Shader* shader) const {
    if (!shader) {
        std::cerr << "ERROR: Null shader in Material!\n";
    }

    shader->setVec3("baseColor", mBaseColor);
        
    shader->setVec3("material.ambient", mAmbient);
    shader->setVec3("material.diffuse", mDiffuse);
    shader->setVec3("material.specular", mSpecular);
    shader->setFloat("material.shininess", mShininess);

    if (textures.empty()){
        shader->setBool("useTexture", false);
        return;
    }
    else {
        shader->setBool("useTexture", true);
    }

    for (const auto& t : textures) {
        if (t.texture) {
            t.texture->Bind(t.unit);
            shader->setInt(t.uniformName, t.unit);
        }
    }
}

void Material::CreateTexture(const std::string& path, GLenum type, const std::string& uniformName, int unit) {

    Texture* tempTex = new Texture(path, type);
    AddTexture(tempTex, uniformName, unit);

}