#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../render/Shader.h"
#include <vector>

class App {
public:

    App(int width, int height);
    ~App();

    void Init();
    void Run();

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);


private:

    GLFWwindow* window;
    int windowWidth;
    int windowHeight;

    // Camera
    glm::vec3 cameraPos, cameraFront, cameraUp;

    bool firstMouse = true;
    float lastX=400, lastY=300;
    float yaw=-90.0f, pitch=0.0f;

    // for render
    unsigned int VAO, texture;
    Shader* shader;


    std::vector<glm::vec3> cubePositions;


    void ProcessInput();
    void Render();

    void BuildCompileShaders();

    float deltaTime;
    float lastFrame;


    // Objects
    class Mesh* cubeMesh;
    class Object* cube;



};
