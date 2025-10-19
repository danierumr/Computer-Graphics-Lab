#pragma once

#include "Light.h"

class DirLight : public Light
{

public:

    DirLight(int index = 0, std::string format = "cube", glm::vec3 direction = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f));

    void SetPropertiesInShader(class Shader* shader) override;

    void Render() const {}

    glm::vec3 mDirection;

};