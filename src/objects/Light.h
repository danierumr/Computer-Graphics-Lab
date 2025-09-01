#pragma once

#include <glm/glm.hpp>
#include <string>

class Light {

public:

    Light(std::string format = "cube");

    void RenderVisual(const class Shader* shader);

    void CreateCubeVisual();
    
    glm::vec3 mPosition;
    glm::vec3 mColor;
    float mIntensity;

    class Object* visual;
    class Mesh* visualMesh;


};