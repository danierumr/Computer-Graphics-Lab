#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../render/Shader.h"
#include <vector>
#include "../objects/Camera.h"

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
    Camera* mCamera;
    bool firstMouse;
    float lastX, lastY;

    // for render
    unsigned int VAO, texture;
    Shader* shader;


    std::vector<glm::vec3> cubePositions;


    void ProcessInput();
    void Render();

    void BuildCompileShaders();

    void OnResize(int w, int h);
    void OnMouseMove(double xpos, double ypos);
    void OnScroll(double xoffset, double yoffset);

    float deltaTime;
    float lastFrame;


    // Objects
    class Mesh* cubeMesh;
    class Object* cube;



};
