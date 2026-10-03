#include "SpotLight.h"
#include "../../render/Shader.h"

SpotLight::SpotLight(int index, std::string format, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : Light(index, format, ambient, diffuse, specular)
{
    mPosition = position;
    mDirection = direction;
}

void SpotLight::SetPropertiesInShader(Shader* shader, int index) {
    shader->setVec3("spotLight.position", mPosition);
    shader->setVec3("spotLight.direction", mDirection);
    shader->setVec3("spotLight.ambient", mAmbient);
    shader->setVec3("spotLight.diffuse", mDiffuse);
    shader->setVec3("spotLight.specular", mSpecular);

    shader->setFloat("spotLight.constant", 1.0f);
    shader->setFloat("spotLight.linear", 0.09f);
    shader->setFloat("spotLight.quadratic", 0.032f);

    shader->setFloat("spotLight.cutOff", 0.09f);
    shader->setFloat("spotLight.outerCutOff", 0.09f);
}
