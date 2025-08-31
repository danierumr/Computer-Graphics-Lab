#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "app/App.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {

    App app(WINDOW_WIDTH, WINDOW_HEIGHT);
    app.Init();
    app.Run();

    return 0;
}