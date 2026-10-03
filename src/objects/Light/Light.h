#pragma once

#include <glm/glm.hpp>
#include <string>

#include "../ComponentRender.h"

class Light  : public ComponentRender
{

public:
    virtual ~Light() = default;

    Light(int index = 0, std::string format = "cube", glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f));

    virtual void SetPropertiesInShader(class Shader* shader, int index = 0);
    
    glm::vec3 mColor;

    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;

};