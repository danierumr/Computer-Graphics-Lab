cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

# Fontes do projeto
set(SOURCES
    src/main.cpp
    src/third_party/glad.c

    src/third_party/stb_image.h
    src/third_party/stb_image.cpp

    src/app/App.h
    src/app/App.cpp

    src/render/Shader.h
    src/render/Shader.cpp

    src/objects/Mesh.h
    src/objects/Mesh.cpp
    src/objects/Object.h
    src/objects/Object.cpp
    src/objects/Texture.h
    src/objects/Texture.cpp
    src/objects/Material.h
    src/objects/Material.cpp
    src/objects/Camera.h
    src/objects/Camera.cpp

)

# Encontrar OpenGL e GLFW
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_executable(RayTracer ${SOURCES})

target_link_libraries(RayTracer PRIVATE OpenGL::GL ${GLFW_LIBRARIES})

# Incluir cabeçalhos
target_include_directories(RayTracer PRIVATE include ${GLFW_INCLUDE_DIRS} /usr/include)