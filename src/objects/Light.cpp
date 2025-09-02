#include "Light.h"
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Light::Light(std::string format) {

    mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    mColor = glm::vec3(1.0f, 1.0f, 1.0f);
    mAmbientIntensity = mDiffuseIntensity = mSpecularIntensity = 1.0f;


    CreateCubeVisual();
}

void Light::RenderVisual(const Shader* shader) {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, mPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    visual->SetModelMatrix(model);
    visual->Render(shader);

}

void Light::CreateCubeVisual() {


    std::vector<Vertex> vertices = {
        // positions        // texture coords
        // Front
        {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        // Back
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
        // Right
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}, {1.0f, 0.0f,  0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, {1.0f, 0.0f,  0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}, {1.0f, 0.0f,  0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, {1.0f, 0.0f,  0.0f}},
        // Left
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}, {-1.0f, 0.0f,  0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, {-1.0f, 0.0f,  0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}, {-1.0f, 0.0f,  0.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, {-1.0f, 0.0f,  0.0f}},
        // Top
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},   {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},   {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        // Bottom
        {{-0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    };

    
    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 3,
        1, 2, 3,
        // Back face
        4, 5, 7,
        5, 6, 7,
        // Right face
        8, 9, 11,
        9, 10, 11,
        // Left face
        12, 13, 15,
        13, 14, 15,
        // Top face
        16, 17, 19,
        17, 18, 19,
        // Bottom face
        20, 21, 23,
        21, 22, 23
    };


    visualMesh = new Mesh(vertices, indices);
    visual = new Object(visualMesh);


    visual->CreateMaterial();
    visual->GetMaterial()->SetBaseColor(glm::vec3(1.0f, 1.0f, 1.0f));

}