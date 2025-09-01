#include "Object.h"

Object::Object(Mesh* mesh) {

    model = glm::mat4(1.0f);
    mMesh = mesh;

}

Object::~Object() {
    delete mMesh;
    delete mMaterial;
}

void Object::CreateMaterial() {

    mMaterial = new Material();

}

void Object::Render(const Shader* shader) const {

    if (!shader || !mMesh) return;

    shader->setMat4("model", model);

    mMesh->Render(shader, mMaterial);

}