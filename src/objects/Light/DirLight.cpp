#include "DirLight.h"
#include "../../render/Shader.h"

DirLight::DirLight(int index, std::string format, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Light(index, format, ambient, diffuse, specular)
{
    mDirection = direction;
}

void DirLight::SetPropertiesInShader(Shader* shader) {

    // TODO: mColor is not implemented in any way

    shader->setVec3("dirLight.direction", mDirection);
    
    shader->setVec3("dirLight.ambient", mAmbient);
    shader->setVec3("dirLight.diffuse", mDiffuse);
    shader->setVec3("dirLight.specular", mSpecular);

}