#include "Light.h"
#include "../Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Light::Light(int index, std::string format, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {

    mColor = glm::vec3(1.0f, 1.0f, 1.0f);
    
    mAmbient = ambient;
    mDiffuse = diffuse;
    mSpecular = specular;
}

void Light::SetPropertiesInShader(Shader* shader) {}