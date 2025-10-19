#include "Pointlight.h"
#include "../../render/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Object.h"


Pointlight::Pointlight(Shader* shader, int index, std::string format, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) 
    : Light(index, format, ambient, diffuse, specular),
    mLightShader(shader)
{   
    CreateCubeVisual();
}

void Pointlight::Render() const {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, mPosition);
    model = glm::scale(model, glm::vec3(0.2f));

    visual->SetModelMatrix(model);
    visual->Render();

}

void Pointlight::CreateCubeVisual() {


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
    visual = new Object(mLightShader, visualMesh);


    visual->CreateMaterial();
    visual->GetMaterial()->SetBaseColor(glm::vec3(1.0f, 1.0f, 1.0f));

}

void Pointlight::SetPropertiesInShader(Shader* shader) {

    // TODO: mColor is not implemented in any way

    shader->setVec3("pointLights[0].position", mPosition);
    shader->setVec3("pointLights[0].ambient", mAmbient);
    shader->setVec3("pointLights[0].diffuse", mDiffuse);
    shader->setVec3("pointLights[0].specular", mSpecular);

    shader->setFloat("pointLights[0].constant", 1.0f);
    shader->setFloat("pointLights[0].linear", 0.09f);
    shader->setFloat("pointLights[0].quadratic", 0.032f);

}