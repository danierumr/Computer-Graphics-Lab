#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texCoord;
};

class Mesh {
    
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void Render(const class Shader* shader, const class Material* material = nullptr) const;

private:

    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;

};
