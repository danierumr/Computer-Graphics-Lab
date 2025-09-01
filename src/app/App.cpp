#include "App.h"
#include <cmath>
#include "../third_party/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../objects/Mesh.h"
#include "../objects/Object.h"
#include "../objects/Texture.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height);}

// void App::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//     if (firstMouse) {
//         lastX = xpos;
//         lastY = ypos;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastX - ypos;
//     lastX = xpos;
//     lastY = ypos;

//     float sensitivity = 0.1f;
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     yaw += xoffset;
//     pitch += yoffset;

//     if (pitch > 89.0f)
//         pitch = 89.0f;
//     if (pitch < -89.0f)
//         pitch = -89.0f;

//     glm::vec3 direction;
//     direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     direction.y = sin(glm::radians(pitch));
//     direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     cameraFront = glm::normalize(direction);
// }


App::App(int width, int height) 
    : window(nullptr), windowWidth(width), windowHeight(height) {

        cubePositions = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };

        cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

        deltaTime = 0.0f;
        lastFrame = 0.0f;

}

App::~App() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void App::Init() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(windowWidth, windowHeight, "RayTracer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glViewport(0, 0, windowWidth, windowHeight);

}

void App::Run() {

    glEnable(GL_DEPTH_TEST);

    BuildCompileShaders();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glfwSetCursorPosCallback(window, App::mouse_callback);

    while (!glfwWindowShouldClose(window)) {

        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();
        
        ProcessInput();

        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

}

void App::ProcessInput() {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    const float cameraSpeed = 2.0f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}

void App::Render() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    shader->setMat4("view", view);
    shader->setMat4("projection", projection);


    for (unsigned int i=0;i<10;i++) {


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        
        cube->SetModelMatrix(model);
        cube->Render(shader);


        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }


    // glBindVertexArray(0);

}

void App::BuildCompileShaders() {

    shader = new Shader("../src/shaders/shader.vs", "../src/shaders/shader.fs");

    std::vector<Vertex> vertices = {
        // positions        // texture coords
        // Front
        {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},
        // Back
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
        // Right
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        // Left
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
       // Top
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
        // Bottom
        {{-0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
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

    cubeMesh = new Mesh(vertices, indices);
    cube = new Object(cubeMesh);
    cube->CreateMaterial();
    cube->GetMaterial()->CreateTexture("../assets/container.jpg");

}
