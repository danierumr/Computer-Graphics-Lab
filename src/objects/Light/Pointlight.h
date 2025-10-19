#pragma once

#include "Light.h"

class Pointlight : public Light {

public:

    Pointlight(class Shader* shader, int index = 0, std::string format = "cube", glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f));

    void SetPropertiesInShader(class Shader* shader) override;

    void Render() const;
    void CreateCubeVisual();

    // Specific attribute(s)
    glm::vec3 mPosition;

    // To show the light
    class Shader* mLightShader; 
    class Object* visual;
    class Mesh* visualMesh;

};