#pragma once

#include <glm/glm.hpp>
#include <string>

#include "ComponentRender.h"

class Light  : public ComponentRender
{

public:

    Light(const class Shader* shader, std::string format = "cube");

    void Render() const;

    void CreateCubeVisual();
    
    glm::vec3 mPosition;
    glm::vec3 mColor;
    float mAmbientIntensity, mDiffuseIntensity, mSpecularIntensity;

    class Object* visual;
    class Mesh* visualMesh;

    const class Shader* mShader;
};