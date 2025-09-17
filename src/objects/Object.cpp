#include "Object.h"

Object::Object(const Shader* shader, Mesh* mesh) {

    model = glm::mat4(1.0f);
    mMesh = mesh;

    mShader = shader;

}

Object::~Object() {
    delete mMesh;
    delete mMaterial;
}

void Object::CreateMaterial() {

    mMaterial = new Material();

}

void Object::Render() const {

    if (!mShader || !mMesh) return;

    mShader->setMat4("model", model);

    mMesh->Render(mShader, mMaterial);

}