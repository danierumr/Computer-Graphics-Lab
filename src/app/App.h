#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../render/Shader.h"

class App {
public:

    App(int width, int height);
    ~App();

    void Init();
    void Run();


private:

    GLFWwindow* window;
    int windowWidth;
    int windowHeight;

    // for render
    unsigned int VAO, texture;
    Shader* shader;


    void ProcessInput();
    void Render();

    void BuildCompileShaders();

};
