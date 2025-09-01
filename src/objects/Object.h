#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "../render/Shader.h"
#include "Material.h"

class Object {

public:

    Object(Mesh* mesh);
    ~Object();
    
    void Render(const Shader* shader) const;

    void CreateMaterial();
    
    void SetPosition(const glm::vec3 &pos) { position = pos; }
    void SetRotation(const glm::vec3 &rot) { rotation = rot; }
    void SetScale(const glm::vec3 &scl) { scale = scl; }
    
    void SetModelMatrix(const glm::mat4 &mat) { model = mat; }
    
    void SetMaterial(Material* m) { mMaterial = m; }
    Material* GetMaterial() { return mMaterial; }

private:
    Mesh* mMesh;
    Material* mMaterial;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 model;

};